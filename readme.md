# Risky

This is my first project in Unreal that mainly focused on recreating the tabletop game RISK and doing it in C++. The other Unreal project I had was in blueprint only. So I am really proud of this project and hope you will appreciate the effort that was put into it. Is was not my first time with c++ but the first time to use it in Unreal Engine.

This is only the first of many personal project that I will make. 


## Here is some Gameplay of the current state of the game


https://github.com/user-attachments/assets/5ec325ce-98e5-4e64-9195-aa4c5bf97e63



## Here is a little preview of the UI in this game


https://github.com/user-attachments/assets/6ca6b3e3-dbdb-493b-b857-e0688f989f93


## Ai behaviour

Each of the AI has to play through 3 phases:

- Deployment
- Attack
- Fortification

For each of those action, they have to make the best choice for them. The one that benefits them the most and reduces the risk of being punished.

For this, they are "simulating" each possible actions to see what the impact on each of them is.

And they are also trying to predict the turn of the enemies (because they need to know if their actions are dangerous).

At the end of their predictions, they are evaluating the map and trying to see if they are in a better situation than before or maybe this is the best position they can be in ...

Just like the Minimax algorithm, they are simply trying to maximize their values and minimize the enemies' values.

All of this leads to interesting gameplay and challenging situations.


## What's next...

My plans for this project are to try to make it feel better, to make it more satisfying without really changing the gameplay.

For example, adding more visual effects, more responsiveness, better audio...

I also plan to make the option have options to modify. Sounds, video quality, resolution or game settings...

The only gameplay option I imagine myself adding is the card system of RISK. (each win over a region gives you a card type. Depending on the combination of cards, you can have more deployments during a specific turn)

And after all of this, I will probably start a new project 😊
