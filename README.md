## Note utils

This repo will contain programs that will help me to create and organise notes.

Programs so far:
* [readmeMaker](##Readme Maker)
* [noteMaker](##Note maker)

### Readme Maker

#### Description

This program will extract metadata from `.md` files given the path. The program will look recursively in subdirectories. The data is stored in map of string where path to the file is the key. The data is multimap of short description and value. Example `tags: A B` will generate two entries `A` and `B` where key is `tags`. Given intro and outro from `.metadata` subdirectory the readme file will be generated:
* intro first
* list of all the tags
* outro

#### List of all the tags

It is the list of tags with hyperlinks to another list sort of like a content list in a book. Tags list will be stored in `.metadata` in `tags.md`. This allows for quick access to notes by tags.
Example readme structure:
---
Some intro text.
* [Tag](.metadata/tags.md#Tag)
* [Tag2](.metadata/tags.md#Tag2)

Some outro text.

---
### Note maker

#### Description

Given title and tags the program generates file with apropriate file name, title, tags, and creation date.

#### Styling

The notes are standarized:
* filename camelCased `exampleNoteTitle`
* title lower cased except firs letter `title: Example note title`
* tags upper case for every tag, tags should be one worded `tags: [ Tag Tag ]`