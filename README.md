# Register Access Layer (RAL)

The Register Access Layer (RAL) provides a method for autogenerating C and C++ interfaces for accessing and easily working with registers within a microcontroller. The interfaces provide simple accessors for each bitset within the register as well as named constants for all the valid values within each bitset.

The RAL tries to enforce correctness as much as possible; using scoped enums where possible and optional validation checks at run-time.
