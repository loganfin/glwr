# glwr

A project experimenting with wrapping GLFW.

## TODO

- [ ] It would be nice if polymorphism worked. i.e, given `WindowResizedEvent`
      and `WindowClosedEvent` inherit from `WindowEvent`, you can subscribe to
      both by subscribing to `WindowEvent`. Like for logging or statistics.

- [ ] Implement a multi-thread debug logger.

  - [ ] Maybe use reflection (experimental std lib implementation or a library)
        for logging purposes.
