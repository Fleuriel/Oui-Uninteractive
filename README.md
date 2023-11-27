# Oui-Uninteractive

Controls: 
W = Move forward
A = Rotate left
S = Move backward
D = Rotate right

Space = spawn object type 1
Right shift = spawn object type 2

P = toggle between fill and wireframe

EDITOR
Master Control Panel toggles sub panels

To add and delete objects:
Objects Panel -> Master Object Manager

To see AABB collision box:
Debug Panel -> Tools -> Display bounding box


# KNOWN BUGS
- Pause Menu textures and hitbox are 'off'
- If 2 enemies are in the same scene and are moving around (Roam state), there is a chance that they can collide with one another as their paths intersect one another
- Player bullets may occasionally get stuck/destroyed mid-air without visually colliding with other objects
- If bullets are shot in the same direction as player movement while the player is at max speed, bullets have the tendency to destroy each other when they collide with one another
- In some extreme edge cases, enemy may choose a node that is outside the "game map". As a result, they will get stuck on the outer walls as they can never reach the end node. During testing, the chance of this happening was extremely low, but not 0%.
- Game window viewport bug: 
    1) File is in wrong folder (e.g. font in texture folder)
    2) Application starts (fullscreen)
    3) Error message pops up
    4) Window loses focus
    5) After pressing 'Ok' and returning to the application window, the game window viewport gets messed up (Bug).
    6) Once another scene is loaded, this bug is gone.
- In general, coordinates may be off in some areas (e.g. mouse, font)