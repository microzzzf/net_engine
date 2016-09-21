SET(SOURCE_FILES 
    observer.cpp 
    subject.cpp
    concrete_subject_1.cpp
    concrete_observer_1.cpp
    concrete_observer_2.cpp)
ADD_LIBRARY(association ${SOURCE_FILES})
