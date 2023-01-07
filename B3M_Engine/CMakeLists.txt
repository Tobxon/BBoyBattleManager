
set(B3M_Engine_public_headers
    
)

set(B3M_Engine_sources
    src/emtpy.cpp
)


add_library(B3M_Engine
    ${B3M_Engine_public_headers}
    ${B3M_Engine_sources}
)
