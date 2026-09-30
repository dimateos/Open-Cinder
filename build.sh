# DOCU:: build + install Cinder from subtree/external folder (Windows/Linux basic)

# env
SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
REPO_DIR="$(cd -- "${SCRIPT_DIR}/../../" && pwd)"
OS_NAME=$( [[ "$(uname -s)" == Linux ]] && echo Linux || echo Windows )

# cfg
BUILD_FOLDER="./build_cinder"
INSTALL_FOLDER="${REPO_DIR}"
COMPILER_ARGS="--parallel"

# args
do_CLEAN=1
do_BUILD=1
do_INSTALL=1

# paths
CINDER_ROOT="${REPO_DIR}/external/cinder"

# cmake
CMAKE_FLAGS=" \
    -DCINDER_BUILD_TESTS=OFF \
    -DCINDER_BUILD_ALL_SAMPLES=OFF \
    -CINDER_DISABLE_AUDIO=ON \
    -CINDER_DISABLE_VIDEO=ON \
    -CINDER_DISABLE_IMGUI=ON \
    #-DBUILD_SHARED_LIBS=OFF \
"

# timing
run() {
    echo
    [ $# -eq 0 ] && { echo ">>> (no command)"; return 1; }
    echo ">>> $*"

    local start=$(date +%s)
    if declare -F "$1" > /dev/null; then "$@"; else "$@"; fi
    local rc=$?
    local end=$(date +%s)

    echo ">>>   RC: $rc"
    echo ">>> TIME: $((end - start)) seconds"
    echo
    return $rc
}

# build
build() {
    local local_BUILD_TYPE="$1"
    local local_BUILD_FOLDER="${BUILD_FOLDER}/${local_BUILD_TYPE}"

    if [[ "$OS_NAME" == "Windows" ]]; then
        LIB_DIR="${INSTALL_FOLDER}/lib/Windows/x86_64/${local_BUILD_TYPE}/cinder"
        GENERATOR='-G "Visual Studio 17 2022" -A x64'
    else
        LIB_DIR="${INSTALL_FOLDER}/lib/Linux/x86_64/${local_BUILD_TYPE}/cinder"
        GENERATOR='-G Ninja'
    fi

    mkdir -p "${LIB_DIR}"

    INSTALL_DIRS=" \
        -DCMAKE_INSTALL_INCLUDEDIR=${INSTALL_FOLDER}/external/cinder \
        -DCMAKE_INSTALL_LIBDIR=${LIB_DIR} \
        -DCMAKE_INSTALL_BINDIR=${LIB_DIR} \
    "

    if [[ "$do_CLEAN" == "1" ]]; then
        echo
        echo +++ Cleaning build: $CINDER_ROOT/$local_BUILD_FOLDER
        rm -rf "$CINDER_ROOT/$local_BUILD_FOLDER"
    fi

    echo
    echo +++ cmake MANAGE

    if [[ "$OS_NAME" == "Windows" ]]; then
        eval cmake -S "$CINDER_ROOT" -B "$local_BUILD_FOLDER" $GENERATOR -DCMAKE_BUILD_TYPE=${local_BUILD_TYPE} ${INSTALL_DIRS} ${CMAKE_FLAGS} || exit 1
    else
        cmake -S "$CINDER_ROOT" -B "$local_BUILD_FOLDER" -G Ninja -DCMAKE_BUILD_TYPE=${local_BUILD_TYPE} ${INSTALL_DIRS} ${CMAKE_FLAGS} || exit 1
    fi

    if [[ "$do_BUILD" == "1" ]]; then
        echo
        echo +++ cmake BUILD
        cmake --build "$local_BUILD_FOLDER" --config ${local_BUILD_TYPE} ${COMPILER_ARGS} || exit 1
    fi

    if [[ "$do_INSTALL" == "1" ]]; then
        echo
        echo +++ cmake INSTALL
        cmake --install "$local_BUILD_FOLDER" --config ${local_BUILD_TYPE} --prefix "${INSTALL_FOLDER}" || exit 1
    fi
}

# main
(
    cd "$REPO_DIR" || exit 1
    echo --- BUILDING CINDER ---
    echo - Target folder: $CINDER_ROOT

    run build Release || exit 1
)
