SET( SRC model.cc material.cc objloader.cc objmaterialloader.cc mll.cc)
INCLUDE_DIRECTORIES( /usr/include )
LINK_DIRECTORIES( /usr/lib )
ADD_LIBRARY( modelloader ${SRC})
