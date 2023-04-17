// The entry file of your WebAssembly module.

export function add(a: i32, b: i32): i32 {
  return a + b;
}

const MAX_WIDTH = 1920
const MAX_HEIGHT = 1080

const inputBuffer = new Array<u8>(MAX_WIDTH * MAX_HEIGHT * 4)
const outputBuffer = new Array<f32>(MAX_WIDTH * MAX_HEIGHT * 3)

const lut = new Array<f32>(256)

export function as_init(): void {
  for (let i = 0; i < MAX_WIDTH * MAX_HEIGHT; i++) {
    inputBuffer[i * 4 + 0] = (i % 255 as u8)
    inputBuffer[i * 4 + 1] = (i % 255 as u8)
    inputBuffer[i * 4 + 2] = (i % 255 as u8)
    inputBuffer[i * 4 + 3] = (i % 255 as u8)
  }
  for (let i = 0; i < 256; i++) {
    lut[i] = (i as f32) / (255 as f32)
  }
}

export function as_naive(width: i32, height: i32): void {
  for (let i = 0; i < width * height; i++) {
    outputBuffer[i * 3 + 0] = inputBuffer[i * 4 + 0] / (255 as f32)
    outputBuffer[i * 3 + 1] = inputBuffer[i * 4 + 1] / (255 as f32)
    outputBuffer[i * 3 + 2] = inputBuffer[i * 4 + 2] / (255 as f32)
  }
}

export function as_lut(width: i32, height: i32): void {
  for (let i = 0; i < width * height; i++) {
    outputBuffer[i * 3 + 0] = lut[inputBuffer[i * 4 + 0]]
    outputBuffer[i * 3 + 1] = lut[inputBuffer[i * 4 + 1]]
    outputBuffer[i * 3 + 2] = lut[inputBuffer[i * 4 + 2]]
  }
}
