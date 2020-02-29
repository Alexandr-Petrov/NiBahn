# NiBahn
Abundantly documented, C project for combining multiple Nibo robots into one managed chain

## Quick information 

### Concept

![Concept](https://github.com/Alexandr-Petrov/NiBahn/blob/master/images/idea.jpg)

We wanted to develop the controllable chain of Nibo robots with following roles:
1. Master - identified by orange lights
2. Slave - identified by green lights
Where we could also address individual robot and control it separately, remove it from the chain and place it back via wireless connection.
For that purpose we used XBee modules on Nibos and on PC.

But to control robots and communicate the roles we had only 8 bits that we could transmit in the TU (transmission unit), so we made our own protocol for communication.

### Protocol

We have divided the 8 bits TU in 4 sections:

- First 2 bits - destination address
- Second 2 bits - source address
- Third 2 bits - the number of actions set
- Fourth 2 bits - the number of action within the set

That was enough to develop all required functions:

### Functions List
1. xxxx0000 - moving forward in the chain
2. xxxx0001 - moving backward in the chain
3. xxxx0010 - change direction via 180 degrees left turn
4. xxxx0011 - change direction via 180 degrees right turn
5. xxxx0100 - moving forward individually
6. xxxx0101 - moving backward individually
7. xxxx0110 - turn 90 degrees left
8. xxxx0111 - turn 90 degrees right
9. xxxx1000 - claim role
10. xxxx1001 - step down in the role if already taken
11. xxxx1010 - reelection
12. xxxx1011 - stop participating in the chain
13. xxxx1100 - stop if Nibo with higher role corrects the direction

Robots also were very unstable in terms of keeping the same direction, so we have placed black line to make them orient on it and automatically correct the movement.

## Functionality showcase videos:

1. Control of the chain, selection of the individual Nibo https://drive.google.com/open?id=1PpwHXfB1GmHDf9-8AqwZouC2QgUBE59_
2. Control of the Individual Nibo, leaving the chain, reentering the chain https://drive.google.com/open?id=19amA65ENEu1S2u_hja86zCAshO6GQEz3
3. Scalability demonstration https://drive.google.com/open?id=1PpwHXfB1GmHDf9-8AqwZouC2QgUBE59_

## Showcase videos are also available with audio comments, in German:
 
https://drive.google.com/drive/folders/1QB2MMK-OmDLlONoJ0xK-Jjj40hYAgM0q?usp=sharing

Mit Hilfe von oben stehendem Link können sie ein Szenarium finden, wo alle Befehlen und Eigenschaften von Auswahlprozess praktisch gezeigt werden.

Inhalt von Videos:
1. Demonstration von Befehlen 1,2,3,4 aus Befehlen Set 1 (Zug Mode) und Befehlen 1,2,3,4 aus Befehlen Set 2 (Selbständiger Nibo)
2. Demonstration von Befehlen 1,2,3,4 aus Befehlen Set 2 (Selbständiger Nibo) und Befehlen 3,4 aus Befehlen Set 3 (Master Prozess)
3. Demonstration von Skalierbarkeit

Reihenfolge von videos:
1->2->3
