## Template for add custom hunter config
# Useful when there is a need for a non-default version or arguments of a dependency,
# or when a project not registered in Hunter should be added.
#
# hunter_config(
#     package-name
#     VERSION 0.0.0-package-version
#     CMAKE_ARGS "CMAKE_VARIABLE=value"
# )
#
# hunter_config(
#     package-name
#     URL https://repo/archive.zip
#     SHA1 1234567890abcdef1234567890abcdef12345678
#     CMAKE_ARGS "CMAKE_VARIABLE=value"
# )

# hunter_config(
#     intx
#     VERSION 0.12.1
#     URL "https://github.com/chfast/intx/archive/refs/tags/v0.12.1.zip"
#     SHA1 "e7db64eec7078e2f705c93991f5fd9b3e3b89634"
# )

hunter_config(
    intx
    VERSION 0.10.0
    URL https://github.com/chfast/intx/archive/v0.10.1.tar.gz
    SHA1 168e0c2ff6760bd6467e25523cc0e68447358018
)
