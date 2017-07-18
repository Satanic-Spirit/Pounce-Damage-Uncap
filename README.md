# Pounce-Damage-Uncap by ProdigySim

https://forums.alliedmods.net/showthread.php?t=182628

This plugin recreates for l4d2 2 cvars available in l4d1. z_pounce_damage_range_max/min.

Maybe not the most accurate name, since this does nothing on its own relative to the cap on pounce damage.

CVars
z_pounce_damage_range_min - The minimum distance for a pounce to be given more than 1 damage.
z_pounce_damage_range_max - The distance at which a pounce is worth its maximum (1+z_hunter_max_pounce_bonus_damage)


Installation
Place the contents of the zip/tar in left4dead2/addons/

Background
Hunter pounce damage is essentially calculated as follows:
PHP Code:
float CalculatePounceDamage(float pounce_distance)
{
    float min_dist = z_pounce_damage_range_min.GetFloat();
    float max_dist = z_pounce_damage_range_max.GetFloat();
    float max_damage = z_hunter_max_pounce_bonus_damage.GetFloat();

    if(pounce_distance <= min_dist) return 1.0;

    if(pounce_distance >= max_dist) return 1.0 + max_damage;

    return 1.0 + (max_damage * (pounce_distance - min_dist) / (max_dist - min_dist));
} 
Basically, this means that pounce damage scales linearly with z_pounce_damage_range_min/max as endpoints (min: 1 damage, max 1+z_hunter_max_pounce_bonus_damage).
However, in L4D2, there is no CVar control of the min_dist and max_dist. This plugin adds those two cvars.

The default values for these cvars are as follows:
z_pounce_damage_range_min: 300.0 (500 in l4d1)
z_pounce_damage_range_max: 1000.0 (same in l4d1)

So, if I pounce someone from 650 units away, I'll do 1 + (24 * 350 / 700) = 13 damage.
If I want to double the pounce damage limit, but keep the same scaling on l4d2, I'd set:

Code:

z_hunter_max_pounce_bonus_damage 49
z_pounce_damage_range_min 300 // same start point
z_pounce_damage_range_max 1729.1666 // ((49 / 24) * 700) + 300

While you might not want to calculate these vars yourself, a plugin like this one can now be adapted for L4D2.

TODO
- Either update a plugin or build in functionality for slope-locked max damage scaling.
- Gamedata perhaps

Changelog
1.0 Initial release.
1.1 Fixed for v2.1.2.5

Source code
The program is GPL v3.
https://github.com/ProdigySim/Pounce-Damage-Uncap

Grab the latest release from here:
https://github.com/ProdigySim/Pounce...Uncap/releases
