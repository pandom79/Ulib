#include "../ulib.h"

typedef struct {
    char *name;
    char *surname;
    int age;
} Person;

typedef struct {
    char *type;
    char *city;
    int num_people;
} Event;

static Person*
personNew() {
    Person *person = calloc(1, sizeof(Person));
    assert(person);
    person->name = NULL;
    person->surname = NULL;
    person->age = 0;
    return person;
}

static void
personRelease(Person **person)
{
    if (*person) {
        objectRelease(&(*person)->name);
        objectRelease(&(*person)->surname);
        objectRelease(person);
    }
}

static Event*
eventNew() {
    Event *event = calloc(1, sizeof(Event));
    assert(event);
    event->type = NULL;
    event->city = NULL;
    event->num_people = 0;
    return event;
}

static void
eventRelease(Event **event)
{
    if (*event) {
        objectRelease(&(*event)->type);
        objectRelease(&(*event)->city);
        objectRelease(event);
    }
}

// INIT PARSER CONFIGURATION

enum SectionNameEnum  {
    PERSON = 0,
    EVENT = 1
};

/* Properties */
enum PropertyNameEnum  {
    NAME = 0,
    SURNAME = 1,
    AGE = 2,
    TYPE = 3,
    CITY = 4,
    NUM_PEOPLE = 5
};

/* Sections */
int SECTIONS_ITEMS_LEN = 2;
SectionData SECTIONS_ITEMS[] = {
    { { PERSON, "[Person]" }, true, true, 0 },
    { { EVENT, "[Event]" }, true, true, 0 },
};

int PROPERTIES_ITEMS_LEN = 6;
PropertyData PROPERTIES_ITEMS[] = {
    { PERSON, { NAME, "Name" },             false, true, false, 0, NULL, NULL },
    { PERSON, { SURNAME, "Surname" },       false, true, false, 0, NULL, NULL },
    { PERSON, { AGE, "Age" },               false, true, true, 0, NULL, NULL },
    { EVENT, { TYPE, "Type" },              false, true, false, 0, NULL, NULL },
    { EVENT, { CITY, "City" },              false, true, false, 0, NULL, NULL },
    { EVENT, { NUM_PEOPLE, "Num_people" },  false, true, true, 0, NULL, NULL },
};

// END PARSER CONFIGURATION

int main()
{
    int rv = 0, numLine = 0, i;
    bool isAggregate = true;
    Array *lineData = NULL, *persons = NULL, *events = NULL;
    Array *errors = arrayNew(objectRelease);
    FILE *fp = NULL;
    const char *filename = "/home/domenico/Progetti/ulib/test/data.txt";
    size_t len = 0;
    char *line = NULL, *error = NULL, *value = NULL;
    PropertyData *propertyData = NULL;
    SectionData *sectionData = NULL;
    Person *person = NULL;
    Event *event = NULL;

    /* Parser initialize */
    parserInit(SECTIONS_ITEMS_LEN, SECTIONS_ITEMS, PROPERTIES_ITEMS_LEN, PROPERTIES_ITEMS);

    /* Open the file */
    if ((fp = fopen(filename, "r")) == NULL) {
        printf("Unable to open %s!\n", filename);
        rv = 1;
        return rv;
    }

    while (getline(&line, &len, fp) != -1) {
        numLine++;
        rv = parseLine(line, numLine, &lineData, &sectionData, &propertyData);
        if (lineData) {
            if ((error = arrayGet(lineData, 2))) {
                assert(rv != 0);
                arrayAdd(errors, stringNew(error));
                if (!isAggregate)
                    break;
                else {
                    arrayRelease(&lineData);
                    continue;
                }
            }
            else {
                if ((value = arrayGet(lineData, 1))) {
                    if (person || event)
                    switch (propertyData->property.id) {
                        case NAME:
                            person->name = stringNew(value);
                            break;
                        case SURNAME:
                            person->surname = stringNew(value);
                            break;
                        case AGE:
                            person->age = atoi(value);
                            break;
                        case TYPE:
                            event->type = stringNew(value);
                            break;
                        case CITY:
                            event->city = stringNew(value);
                            break;
                        case NUM_PEOPLE:
                            event->num_people = atoi(value);
                            break;
                    }
                }
                else {
                    switch (sectionData->section.id) {
                        case PERSON:
                            person = personNew();
                            if (!persons)
                                persons = arrayNew(personRelease);
                            arrayAdd(persons, person);
                            break;
                        case EVENT:
                            event = eventNew();
                            if (!events)
                                events = arrayNew(eventRelease);
                            arrayAdd(events, event);
                            break;
                        default:
                            break;
                    }
                    /*
                    * If the section is repeatable then we must
                    * check the required data and clean the properties counters
                    * before to start another one.
                    */
                    if (parserCheckCurSec(&errors, isAggregate) != 0)
                        goto out;
                }
            }
        }
        arrayRelease(&lineData);
    }

    out:
        parserEnd(&errors, isAggregate);
        if (errors && errors->size > 0) {
            rv = 1;
            for (int i = 0; i < errors->size; i++)
                printf("Error [%d] = %s\n", i, (char *)arrayGet(errors, i));
        }

        for (i = 0; i < persons->size; i++) {
            Person *p = arrayGet(persons, i);
            printf("Person %d = %s ...\n", i, p->name);
        }
        for (i = 0; i < events->size; i++) {
            Event *e = arrayGet(events, i);
            printf("Event %d = %s ...\n", i, e->city);
        }

        arrayRelease(&persons);
        arrayRelease(&events);
        arrayRelease(&errors);
        arrayRelease(&lineData);
        objectRelease(&line);
        fclose(fp);
        fp = NULL;
        return rv;
}
