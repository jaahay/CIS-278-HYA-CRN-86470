# Core Event & State System

A modular, extensible, and type-safe C++20 core library for event-driven state management.

---

## Features

- **Polymorphic singleton states:** Identity-based, immutable states using CRTP.
- **Compile-time concepts:** Enforce correctness of states, events, and callbacks.
- **Hierarchical event dispatch:** Supports callback invocation by event type hierarchy.
- **Phase-aware callbacks:** Before, Main, and After phases with ordered invocation.
- **Priority-based callback ordering:** Flexible singleton priority states with relative ordering.
- **Thread-safe:** Safe concurrent callback registration, removal, and dispatch.
- **Exception safe:** Robust dispatch with callback exception handling.
- **RAII callback lifetime management:** Scoped handles for automatic unregistering.
- **Compile-time meta utilities:** Tuple and variant composition, cycle detection for priority relations.

---

## Directory Structure

/include
  /core
    concepts/
      Concepts.h
    event/
      CallbackPhaseState.h
      DefaultPriorityState.h
      Event.h
      EventCallback.h
      EventDispatcher.h
      EventHierarchy.h
      PriorityState.h
      ScopedCallbackHandler.h
    meta/
      Meta.h
      Tuple.h
      Variant.h
      TypeList.h
      CycleCheck.h
    state/
      BaseState.h
      TemplateState.h
/src
  /core
    CMakeLists.txt

---

## Extending the System

- Define your own singleton state types for domain-specific states or priorities.
- Specialize `EventHierarchy` to declare event type inheritance chains for hierarchical dispatch.
- Use `ScopedCallbackHandler` for safe, automatic callback lifetime management.
- Use `core::meta::CycleCheck` to verify priority declarations are cycle-free at compile time.

---

## Testing

Unit tests are located in `/tests/core/` and cover:

- State identity and ordering
- Event dispatch and callback invocation order
- Priority sorting correctness
- Compile-time concept enforcement

Run tests with your preferred C++ test framework.

---

## Acknowledgments

This core system was developed with assistance from Ecosia AI, an AI-powered research assistant focused on sustainable and principled software design.

---

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

For questions or contributions, please contact [Your Contact Info].
