##### **# UI Architecture**



**## General Principles**



The UI system does not use MVVM.



Widgets are allowed to access gameplay data directly when needed.

This is a deliberate design choice to avoid unnecessary abstraction

and boilerplate.



**## Pawn Binding**



Widgets are not automatically rebound to new pawns.



When the controlled pawn changes, `InitWidgetPawnOwner` must be called

explicitly to update widget references.



This makes ownership changes predictable and explicit.



**## Rationale**



* MVVM adds complexity without clear benefits in this project.
* Explicit binding is easier to debug.
* UI logic remains transparent and controllable.







##### **#Action Blocking System in AHBaseCharacter**



The project uses a bitmask-based ActionRestriction system to restrict
character actions (movement, attack, etc).

Each restriction is represented as a flag in a bitmask and can be
combined using the bitwise OR (`|`) operator.



**## Lifetime Management**



The ActionRestriction system does NOT use RAII.

Adding and removing restrictions is handled manually.

Any system that adds a restriction is responsible for removing it
explicitly.

Example:

* Ability starts → adds restriction
* Ability ends → removes restriction

Restrictions are not automatically removed when an object goes out
of scope.



**## Rationale**



RAII is intentionally not used because:

* Restrictions often outlive a single function scope
* Their lifetime depends on gameplay events
* Automatic destruction could remove restrictions prematurely
* Explicit control improves predictability

This design ensures that blocks are removed only at well-defined
logical points in gameplay.



**## Usage Guidelines**



* Always store the added mask
* Always remove exactly the same mask
* Use `|` to combine multiple restrictions
* Never rely on destructors for cleanup
