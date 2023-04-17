const std = @import("std");
const testing = std.testing;

const buffer_size = 1920 * 1080 * 4;
const buffer: [buffer_size]u8 = [_]u8{0} ** buffer_size;

export fn getBufferPtr() usize {
    return @ptrToInt(&buffer);
}

export fn add(a: i32, b: i32) i32 {
    return a + b;
}

test "basic add functionality" {
    try testing.expect(add(3, 7) == 10);
}
