# Find includes in corresponding build directories

SET(INDIGO_MOC_SOURCES
    indigo.h
)

SET(INDIGO_SOURCES
    indigo.cpp
)

QT5_WRAP_CPP(INDIGO_MOC_SOURCES
    ${INDIGO_MOC_CLASSES}
)


ADD_EXECUTABLE(indigo
    ${INDIGO_MOC_SOURCES}
    main.cpp
    ${INDIGO_SOURCES}
)

#target_link_libraries(indigo Qt5::Core)
TARGET_LINK_LIBRARIES(indigo
    Qt5::Core
)
