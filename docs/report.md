# Report

**Author:** Чигиренко Егор  
**Topic:** BMP image processing tool with multi-threaded operations  
**Tests:** Google Test

---

## Main Features

1. **Multi-threaded Processing**: optimal performance is achieved by leveraging all CPU cores.
2. **Modular Architecture**: a clean separation of algorithms is maintained through a modular architecture.
3. **Optimized Algorithms**: fast operations are guaranteed by the use of optimized algorithms.
4. **BMP Format Support**: the processor supports standard BMP files that have a 24-bit color depth.

## Performance Metrics

| Operation                    | Before Optimization (ms) | After Optimization (ms)| coefficient |
|------------------------------|--------------------------|------------------------|-------------|
| Clockwise Rotation           | 15689                    | 5742                   | 2.732       |
| Counterclockwise Rotation    | 7821                     | 5264                   | 1.486       |
| Gaussian Filter              | 526207                   | 5078                   | 103.625     |

---

## Test info

| Test                     | Output                                                             |
|--------------------------|--------------------------------------------------------------------|
| BMPReadInvalidFile       | None-existing file has been checked and skipped                    |
| BMPSetDimensions         | Image dimension settings have been tested                          |
| BMPSaveFile              | File saving has been verified correctly                            |
| RotateCounterClockwise   | Counter-clockwise rotation has been tested                         |
| RotateClockwise          | Clockwise rotation has been tested                                 |
| DoubleRotationIdentity   | Rotation identity has been verified                                |
| GaussianFilterSmallCore  | Small gaussian core filtering has been tested                      |
| GaussianFilterLargeSigma | Large gaussian sigma (σ) value filtering has been tested           |
| RotateThenFilter         | Combination of rotation and filtering has been tested              |
| FilterThenRotateThenSave | Complex combination of some operations with saving has been tested |

## Context
1. The tests uses temporary `test.bmp` file (3x3 pixels)
2. All secondary files are cleaned up after execution due to `TearDown`
3. The tests confirm both operation correctness and image dimension preservation
4. Rectangular images can be checked by redactor or by analyzing `1.bmp` image (make --> ./run)

---

## Corollary
After some optimization and involving of all CPU cores, image processing was significantly accelerated.
