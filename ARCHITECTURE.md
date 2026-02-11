\# UI Architecture



\## General Principles



The UI system does not use MVVM.



Widgets are allowed to access gameplay data directly when needed.

This is a deliberate design choice to avoid unnecessary abstraction

and boilerplate.



\## Pawn Binding



Widgets are not automatically rebound to new pawns.



When the controlled pawn changes, `InitWidgetPawnOwner` must be called

explicitly to update widget references.



This makes ownership changes predictable and explicit.



\## Rationale



\- MVVM adds complexity without clear benefits in this project.

\- Explicit binding is easier to debug.

\- UI logic remains transparent and controllable.

