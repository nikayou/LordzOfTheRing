# Lordz Of The Ring

## Presentation

Lordz of the ring is a fighting game developed in C++ using SFML 2.0. The goal was to create a game whose controls were simple, and fun immediate.  This was my summer project in 2013, and my second personnal video game.

## Features

_Elements with '*' are not implemented yet._

### Easy gameplay

Only 6 inputs : 3 attacks, and 3 dodges to react against. Only 4 stats for characters, 2 gauges to manage.

### 2 players splitscreen

The game was designed to be played with a friend on the same computer. The screen is separated vertically (as in Wii Boxe) so that each player has an equal vision of the game (not like tennis game where a the top player is disadvantaged).

### Game customisation

There are several options you can modify for the match : victory type, rounds number, rounds time, and modifiers for health and stamina.

### Different characters *

The game has been maked in a way that allows easily to add new characters, with their own stats. (For now, there are only 2 characters, in fact the longest part is to create the graphics for new characters).

### Network game *

If I have time, I will try to add network gaming with a friend whose IP is known.

### AI *

If I have time, I will try to add computer controlled opponents.

## Gameplay

### Basics

There are only 3 attacks : Left Attack, Right Attack, and Middle Attack. Each attack can be dodged in one direction : Left incoming attacks can be dodged by the right...  
Left and Right attacks has the same strength, but the Middle attack (uppercut) is more powerful. However, it's easier to dodge and more punitive when missed.  

### Vulnerability
Each attack consumes stamina : once you run out of stamina, you're character needs to recover : you're vulnerable ! So watch out !  
When you take several hits without attacking or dodging, you're character has a chance to be stun. Calm down and try to dodge to avoid that ! 

### Win a match

There are 4 ways to win a match : by KO number, by rounds, by damages, or by TKO.

##### KO number
After the number of rounds defined in the settings, we are counting each KO on both side : the player who performed the most wins the match.  

##### Rounds
After each round, we count the number of KOs of each side. The player who performed the most wins a points. After all rounds, the player who earned the most points wins the match. Note that between rounds, characters recover all their health.

##### Damage
Here, only inflected damage count, for all the rounds.

##### TKO
For every other win type, you can choose to set TKO victory : when one performs 5 KOs in 1 round, this is a TKO.  Note that after each KO you recover a part of health (decreasing with number of KOs). 

### Stats

Stats set are what differences two characters. 

##### Health
Increase the total amount of health of the character. The more health you have, the more attacks you can bear.

##### Stamina
A high stamina allows to performs more attacks before being tired.

##### Strength
A strong character will do more damage during attacks.

##### Resistance
The chances of being stun while being comboed are reduced with a high resistance.
