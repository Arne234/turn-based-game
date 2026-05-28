🎮 Turn-Based Game (C++ Console RPG)

A simple turn-based combat game written in C++ featuring multiple enemy types, status effects, and a basic AI system.

📌 Features
🧍 Player vs AI turn-based combat
🤖 Multiple enemy types:
Goblin (poison mechanic)
Tank (stun ability, defensive playstyle)
Mage (special attack flavor)
Boss (strong attack ability)
❤️ HP system with max HP limits
🛡️ Defend mechanic (damage reduction)
☠️ Status effects:
Poison (damage over time)
Stun (skip turn mechanic)
⚔️ Critical hits & random damage variance
🧠 Simple enemy AI (takeTurn() system)
🏭 Enemy Factory pattern for enemy creation
🎮 Gameplay

The player chooses an action each turn:

A → Attack
H → Heal
D → Defend
S → Strong Attack (high risk / high reward)

Enemies act automatically based on AI logic.

Win by reducing the enemy HP to 0 before yours reaches 0.

🧠 Core Systems
🔁 Turn System

Each game loop consists of:

Apply status effects
Player action
Enemy turn
Win/Lose check
