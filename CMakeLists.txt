cmake_minimum_required(VERSION 3.10)

project(spade)

set(SRC "Spade")
set(SOURCES 
    ${SRC}/main.cpp
    ${SRC}/Card.cpp
    ${SRC}/Deck.cpp
    ${SRC}/Game.cpp
    ${SRC}/Player.cpp
    ${SRC}/Round.cpp


    # Uncomment these if you want them in your IDE, you generally
    # shouldn't add header files to the executable, however
    #${SRC}/icMatrix.H
    #${SRC}/icVector.H
    #${SRC}/learnply_io.h
    #${SRC}/ply.h
    #${SRC}/tmatrix.h
    #${SRC}/trackball.h
    #${SRC}/polyhedron.h
)

add_executable(Spade ${SOURCES})
set_property(TARGET Spade PROPERTY CXX_STANDARD 11)

set(EIGEN ${CMAKE_CURRENT_SOURCE_DIR}/Eigen-3.4.0)

if (WIN32)
    set(OPENGL ${CMAKE_CURRENT_SOURCE_DIR}/Opengl)
    

    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SAFESEH:NO") 


    target_include_directories(Spade PRIVATE ${OPENGL}/include ${EIGEN})
    target_link_directories(Spade PRIVATE ${OPENGL}/lib)

    target_link_libraries(Spade PRIVATE GLAUX GLU32 glut32 OPENGL32 glew32)


    # Copy DLLs to build directory
    set(TO_COPY
        ${OPENGL}/lib/GLU32.DLL
        ${OPENGL}/lib/glut32.dll
        ${OPENGL}/lib/OPENGL32.DLL
        ${OPENGL}/lib/glew32.dll
    )

    add_custom_command(
        TARGET Spade POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${TO_COPY}
        ${CMAKE_CURRENT_BINARY_DIR}
    )
else()
    find_package(OpenGL REQUIRED)
    find_package(GLUT REQUIRED)

    target_include_directories(Spade PRIVATE
        ${OPENGL_INCLUDE_DIRS}
        ${GLUT_INCLUDE_DIRS}
        ${EIGEN}
    )

    target_link_libraries(Spade PRIVATE
        ${OPENGL_LIBRARIES}
        ${GLUT_LIBRARIES}
    )

    # Silence OpenGL deprecation warnings on Mac
    if(APPLE)
        add_definitions(-DGL_SILENCE_DEPRECATION)
    endif()
endif()
