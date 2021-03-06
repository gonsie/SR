PROJECT(ROSS C)
INCLUDE_DIRECTORIES(${ROSS_SOURCE_DIR} ${ROSS_BINARY_DIR})

SET(ross_srcs

queue/tw-queue.h
queue/${QUEUE}.c

ross-random.h
ross-random.c
rand-${RAND}.h
rand-${RAND}.c

clock/${CLOCK}.h
clock/${CLOCK}.c

ross-gvt.h
gvt/${GVT}.h
gvt/${GVT}.c

ross-network.h
network-${NETWORK}.h
network-${NETWORK}.c

hash-quadratic.h
hash-quadratic.c

buddy.h
buddy.c
lz4.h
lz4.c
tw-state.c

ross-extern.h
ross-global.c

ross-inline.h
ross-kernel-inline.h
ross.h
ross-types.h

tw-eventq.h
tw-event.c

tw-opts.h
tw-opts.c

tw-pe.c
tw-kp.c
tw-lp.c

tw-timing.h
tw-timing.c

tw-sched.c
tw-setup.c
tw-signal.c
tw-stats.c
tw-util.c)


# ROSS VERSION INFORMATION
## Print Date and Time at top of ROSS output
INCLUDE (CheckFunctionExists)
CHECK_FUNCTION_EXISTS(ctime HAVE_CTIME)
## Print ROSS Git Hash
INCLUDE(GetGitRevisionDescription)
GET_GIT_HEAD_REVISION(GIT_REFSPEC GIT_SHA1)

# Data Structure for remote Events
# If AVL_TREE is OFF, ROSS reverts to hashing
OPTION(AVL_TREE "Use AVL trees for optimistic mode events? (hash tabels otherwise)" ON)
SET(AVL_TREE_SIZE 18 CACHE STRING "AVL Treet contians 2^AVL_TREE_SIZE nodes")
IF(AVL_TREE)
  SET(ross_srcs ${ross_srcs} avl_tree.h avl_tree.c)
  MATH( EXPR AVL_NODE_COUNT "1 << ${AVL_TREE_SIZE}" )
ENDIF(AVL_TREE)

# ROSS_MEMORY is either on or off depending on whether or not we desire
# memory buffers.  If it's not set to YES, it defaults to NO
OPTION(ROSS_MEMORY "ROSS Memory Buffers (membufs)" OFF)
IF(ROSS_MEMORY)
  SET(ross_srcs ${ross_srcs} tw-memory.c tw-memoryq.h tw-memory.h)
ENDIF(ROSS_MEMORY)

OPTION(RAND_NORMAL "Turn on state for normal distribution" ON)

# Show timing data at end of run
OPTION(ROSS_timing "Perform ROSS timings" ON)

# Used by ross-kernel-inline.h
OPTION(ROSS_runtime_checks "Perform ID checks" OFF)
IF(CMAKE_BUILD_TYPE MATCHES Debug)
	SET(ROSS_runtime_checks ON CACHE BOOL "Perform ID checks" FORCE)
ENDIF(CMAKE_BUILD_TYPE MATCHES Debug)

# Set all options
#SET(OPTIONS "${OPTIONS} -DROSS_QUEUE_${QUEUE} -DROSS_RAND_${RAND} -DROSS_NETWORK_mpi -DROSS_CLOCK_${CLOCK} -DROSS_GVT_${GVT} -DARCH_${ARCH}")
#SET(OPTIONS "${OPTIONS} -DROSS_QUEUE_${QUEUE} -DROSS_RAND_${RAND} -DROSS_NETWORK_mpi -DROSS_CLOCK_${CLOCK} -DROSS_GVT_${GVT} -DARCH_${ARCH}" PARENT_SCOPE)
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DROSS_OPTION_LIST='\"${OPTIONS}\"'")

# Generate Library
ADD_LIBRARY(ROSS ${ross_srcs})

# Build Specific Config Header
CONFIGURE_FILE(config.h.in config.h)

# CODES config bin
CONFIGURE_FILE(ross-config.in ross-config @ONLY)

# Make Install
INSTALL(TARGETS ROSS DESTINATION lib)
INSTALL(FILES ${ROSS_BINARY_DIR}/ross-config DESTINATION bin PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)
INSTALL(FILES ${ROSS_BINARY_DIR}/config.h DESTINATION include/)
INSTALL(DIRECTORY ${ROSS_SOURCE_DIR}/ DESTINATION include/ FILES_MATCHING PATTERN "*.h")
