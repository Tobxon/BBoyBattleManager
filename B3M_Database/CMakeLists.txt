
set(B3M_Database_public_headers
    
)

set(B3M_Database_sources
    src/emtpy.cpp
)


add_library(B3M_Database
    ${B3M_Database_public_headers}
    ${B3M_Database_sources}
)

