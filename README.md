
# Pacman Game

During the project we implemented the game "Pac-Man".
We read the number of rows and columns of each step from the file, and then built a board of a suitable size for each step and step, with the number of figures and the size of the board varying according to the number of rows and columns in that step.
The game features two main characters:
Pacman - the main actor, whose goal is to eat all the cookies at each stage.
Elf - There are two types of elves: a smart elf - chasing the Pacman, a random elf - spinning freely and randomly. The purpose of the elves is to kill Pacman.
Additional objects in the game:
Cookies - the ones Pacman eats. There are three types of cookies: regular, healthy and toxic. When the Pacman eats healthy cookies his speed increases and when he eats toxic cookies his speed decreases.
Walls - Barriers that are placed at every stage and prevent players from passing through them.


## Technologies
Work environment: visual studio
Technologies: C++ | SFML| OOP | Design patterns

## Main data structures
- StaticObject vector representing the board. It retains all static objects and calls them polymorphically.
- Singleton template: This template is intended for cases where you want to limit the creation of instances of a particular class to a single instance. It is useful when only one instance is required to coordinate system operations. In this program we implemented Singleton in the ResourceManager department which is responsible for uploading the images, since we wanted each image to be uploaded only once.
- map: A dictionary implemented by a balanced search tree in which each node retains a key and value. We used this data structure in the ResourceManager class where we saved the uploaded images.
-: double dispatch A special mechanism for sending one function several times with different objects at a time. The collide function, which handles in-game collisions, uses this mechanism.

## Algorithms
- Various functions for the realization of polymorphism, such as the moving function which is in DynamicObjec as a pure virtual function, is implemented in the classes that inherit each object. Named each time according to the character now being voted on.
- Both the constructor and the distractor operate by polymorphism.
Collide functions - Since there are differences between the collision and different objects, we have created several functions with the same prototype for each active object and passive object.
These functions work with double dispatch

## Demo

Insert gif or link to demo


## Deployment

To deploy this project run

```bash
  npm run deploy
```

## Documentation

[Documentation](https://linktodocumentation)


## Environment Variables

To run this project, you will need to add the following environment variables to your .env file

