const std = @import("std");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const lib = b.addStaticLibrary(.{
        .name = "byte_buffer_cpp",
        .target = target,
        .optimize = optimize,
    });
    lib.stack_protector = false;
    lib.disable_sanitize_c = true;
    lib.linkLibCpp();
    lib.addCSourceFiles(&.{
        b.pathJoin(&.{ "src", "UnsafeByteBuffer.cpp" }),
        b.pathJoin(&.{ "src", "ByteBuffer.cpp" }),
    }, &.{});

    b.installArtifact(lib);

    header(b, &lib.step, "UnsafeByteBuffer.hpp");
    header(b, &lib.step, "ByteBuffer.hpp");
}

fn header(b: *std.Build, step: *std.build.Step, name: []const u8) void {
    step.dependOn(&b.addInstallHeaderFile(b.pathJoin(&.{ "src", name }), name).step);
}
