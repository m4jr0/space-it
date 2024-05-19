#!/bin/sh

# Copyright 2024 m4jr0. All Rights Reserved.
# Use of this source code is governed by the MIT
# license that can be found in the LICENSE file.

if [ -z "$1" ]; then
    build_type="debug"
else
    build_type="$1"
fi

if [ -z "$2" ]; then
    clear_build="false"
else
    clear_build="$2"
fi

if [ "$build_type" != "debug" ] && [ "$build_type" != "release" ]; then
    echo "Invalid argument. Defaulting to debug."
    build_type="debug"
fi

if [ "$clear_build" != "true" ] && [ "$clear_build" != "false" ]; then
    echo "Invalid clear flag argument. Defaulting to false."
    clear_build="false"
fi

echo "Build type is: $build_type"

script_dir="$(cd "$(dirname "$0")" && pwd)"
repo_url="https://github.com/m4jr0/space-it-tools/"
commit_hash="cc2e6b673dc067c7304bd72012fa63ea9cef8d90"
project_dir="$(dirname "$script_dir")"
tools_dir="$project_dir/tools"
build_dir="$tools_dir/lib_build"

if [ "$clear_build" = "true" ]; then
    echo "Clearing directories:"
    echo "- $build_dir"
    echo "- $tools_dir"

    if [ -d "$build_dir" ]; then
        rm -rf "$build_dir"
    fi

    if [ -d "$tools_dir" ]; then
        rm -rf "$tools_dir"
    fi
fi

echo "Setting up tools..."

git --version >/dev/null 2>&1

if [ $? -ne 0 ]; then
    echo "Git is not installed! Please install Git and try again."
    exit 1
fi

if [ ! -d "$tools_dir" ]; then
    git clone --no-checkout "$repo_url" "$tools_dir"

    if [ $? -ne 0 ]; then
        echo "Failed to clone the project."
        exit 1
    fi

    cd "$tools_dir" || exit
    git checkout "$commit_hash"

    if [ $? -ne 0 ]; then
        echo "Failed to checkout the specified commit: $commit_hash"
        exit 1
    fi
fi

if [ ! -d "$build_dir" ]; then
    mkdir "$build_dir"

    if [ $? -ne 0 ]; then
        echo "Failed to create build directory: $build_dir"
        exit 1
    fi
fi

cmake --version >/dev/null 2>&1

if [ $? -ne 0 ]; then
    echo "CMake is not installed! Please install CMake and try again."
    exit 1
fi

cd "$build_dir" || exit

echo "Configuring build..."

cmake "$project_dir" -DVCPKG_ROOT="$project_dir/vcpkg" -DIS_VCPKG_CLONE=TRUE -DCMAKE_build_type="$build_type" -DSID_IS_LIB_BUILD_ONLY=TRUE

if [ $? -ne 0 ]; then
    echo "CMake configuration failed."
    exit 1
fi

echo "Building..."

cmake --build "$build_dir"

if [ $? -ne 0 ]; then
    echo "Build failed."
    exit 1
fi

generated_lib="$build_dir/libsid_lib.a"
dest_lib_dir="$tools_dir/lib"

if [ ! -d "$dest_lib_dir" ]; then
    mkdir "$dest_lib_dir"

    if [ $? -ne 0 ]; then
        echo "Failed to create destination lib directory!"
        exit 1
    fi
fi

cp "$generated_lib" "$dest_lib_dir"

if [ $? -ne 0 ]; then
    echo "Failed to copy sid_lib.Lib."
    exit 1
fi

cd "$tools_dir" || exit
cargo --version >/dev/null 2>&1

if [ $? -ne 0 ]; then
    echo "Cargo is not installed or not in the PATH!"
    exit 1
fi

if [ "$build_type" = "release" ]; then
    cargo build --release
else
    cargo build
fi

if [ $? -ne 0 ]; then
    echo "Something wrong happened while building the tool binaries!"
    exit 1
fi

"$tools_dir/target/$build_type/sid_aseprite_converter" "$project_dir/raw_assets/" "$project_dir/assets/"

if [ $? -ne 0 ]; then
    echo "Something wrong happened while converting the Aseprite files to assets!"
    exit 1
fi

"$tools_dir/target/$build_type/sid_asset_packer" "$project_dir/assets/" "$project_dir/build/resources/"

if [ $? -ne 0 ]; then
    echo "Something wrong happened while exporting the resources!"
    exit 1
fi

exit 0
