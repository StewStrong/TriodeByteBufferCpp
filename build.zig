const std = @import("std");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const lib = b.addStaticLibrary(.{
        .name = "byte_buffer_cpp",
        .target = target,
        .optimize = optimize,
    });
    lib.linkLibCpp();
    lib.addCSourceFiles(&.{
        b.pathJoin(&.{ "src", "UnsafeByteBuffer.cpp" }),
        b.pathJoin(&.{ "src", "ByteBuffer.cpp" }),
    }, &.{});

    b.installArtifact(lib);

    _ = b.addInstallHeaderFile(b.pathJoin(&.{ "src", "UnsafeByteBuffer.hpp" }), "UnsafeByteBuffer.hpp");
    _ = b.addInstallHeaderFile(b.pathJoin(&.{ "src", "ByteBuffer.hpp" }), "ByteBuffer.hpp");
}
