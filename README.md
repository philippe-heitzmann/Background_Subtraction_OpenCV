# Background Subtraction with OpenCV

A comprehensive project implementing video background subtraction using OpenCV C++ and Python methods. This project evaluates multiple background subtraction algorithms and provides tools for performance analysis and visualization.

## Project Overview

This project implements and evaluates various background subtraction algorithms available in OpenCV, including MOG, GMG, CNT, LSBP, and GSOC methods. It provides both C++ and Python implementations with evaluation tools for comparing algorithm performance on different video sequences.

## Features

- Multiple background subtraction algorithms (MOG, GMG, CNT, LSBP, GSOC)
- Performance evaluation with precision, recall, F1-score, and accuracy metrics
- Support for Change Detection 2014 dataset format
- C++ implementation for real-time processing
- Python evaluation pipeline with Jupyter notebook
- Video generation from image sequences
- Comprehensive algorithm comparison tools

## Prerequisites

### System Requirements
- macOS, Linux, or Windows
- Python 3.6 or higher
- C++ compiler (GCC, Clang, or MSVC)
- CMake 3.10 or higher

### Dependencies

#### Python Dependencies
```
opencv-python>=4.5.0
opencv-contrib-python>=4.5.0
numpy>=1.16.0
matplotlib>=3.0.0
pandas>=1.0.0
scikit-learn>=0.20.0
Pillow>=8.0.0
tqdm>=4.50.0
hdbscan>=0.8.0
```

#### C++ Dependencies
- OpenCV 4.5.0 or higher with contrib modules
- C++11 compatible compiler

## Installation

### 1. Clone the Repository
```bash
git clone <repository-url>
cd Background_Subtraction_OpenCV
```

### 2. Python Environment Setup

#### Using Conda (Recommended)
```bash
# Create a new conda environment
conda create -n bgsub python=3.8

# Activate the environment
conda activate bgsub

# Install OpenCV with contrib modules
conda install -c conda-forge opencv

# Install additional dependencies
pip install -r requirements.txt
```

#### Using pip
```bash
# Create virtual environment
python -m venv bgsub_env

# Activate virtual environment
# On macOS/Linux:
source bgsub_env/bin/activate
# On Windows:
bgsub_env\Scripts\activate

# Install dependencies
pip install -r requirements.txt
```

### 3. C++ Setup

#### macOS with Homebrew
```bash
# Install OpenCV with contrib modules
brew install opencv

# Compile the C++ code
cd opencv-test
mkdir build
cd build
cmake ..
make
```

#### Ubuntu/Debian
```bash
# Install OpenCV development packages
sudo apt-get update
sudo apt-get install libopencv-dev libopencv-contrib-dev

# Compile the C++ code
cd opencv-test
mkdir build
cd build
cmake ..
make
```

#### Windows with Visual Studio
1. Download and install OpenCV from https://opencv.org/releases/
2. Set up environment variables for OpenCV
3. Open the project in Visual Studio
4. Build the solution

## Usage

### Python Evaluation Pipeline

#### 1. Prepare Dataset
The evaluation script expects datasets in the Change Detection 2014 format:
```
dataset/
├── sequence_name/
│   ├── input/          # Input frames (.jpg)
│   └── groundtruth/    # Ground truth masks (.png)
```

#### 2. Run Evaluation
```bash
# Evaluate all algorithms on a dataset
python evaluation/background_subtraction_evaluation.py --dataset_path /path/to/dataset

# Evaluate specific algorithm
python evaluation/background_subtraction_evaluation.py --algorithm GSOC --dataset_path /path/to/dataset
```

#### 3. Available Algorithms
- `MOG`: Mixture of Gaussians
- `GMG`: Godbehere, Matsukawa, Goldgof
- `CNT`: Counting
- `LSBP-vanilla`: Local SVD Binary Pattern (vanilla)
- `LSBP-speed`: Local SVD Binary Pattern (speed optimized)
- `LSBP-quality`: Local SVD Binary Pattern (quality optimized)
- `LSBP-camera-motion-compensation`: LSBP with camera motion compensation
- `GSOC`: Graph-based Segmentation of Objects and Clutter
- `GSOC-camera-motion-compensation`: GSOC with camera motion compensation

#### 4. Jupyter Notebook
```bash
# Start Jupyter notebook
jupyter notebook notebooks/Background_Subtraction_Evaluation_Pipeline.ipynb
```

### C++ Implementation

#### 1. Compile
```bash
cd opencv-test
mkdir build
cd build
cmake ..
make
```

#### 2. Run
```bash
# Run with default video (vtest.avi)
./opencv-test

# Run with specific video and algorithm
./opencv-test --input /path/to/video.mp4 --algo MOG2

# Run with KNN algorithm
./opencv-test --input /path/to/video.mp4 --algo KNN
```

#### 3. Command Line Options
- `--input`: Path to input video or image sequence
- `--algo`: Background subtraction method (KNN, MOG2)
- `--help`: Show help information

## Project Structure

```
Background_Subtraction_OpenCV/
├── evaluation/
│   └── background_subtraction_evaluation.py  # Python evaluation script
├── notebooks/
│   └── Background_Subtraction_Evaluation_Pipeline.ipynb  # Jupyter notebook
├── opencv-test/
│   ├── opencv-test.cpp                       # C++ implementation
│   └── build/                                # Build directory (created)
├── README.md                                 # This file
├── objectives.md                             # Project objectives
├── .gitignore                               # Git ignore file
└── requirements.txt                         # Python dependencies
```

## Performance Metrics

The evaluation script calculates the following metrics:
- **Accuracy**: Overall correctness of the segmentation
- **Precision**: True positives / (True positives + False positives)
- **Recall**: True positives / (True positives + False negatives)
- **F1-Score**: Harmonic mean of precision and recall
- **Processing Time**: Average time per frame

## Sample Results

Based on evaluation on the Change Detection 2014 dataset:

### Baseline Highway Sequence
| Algorithm | Precision | Recall | F1-Score | Accuracy |
|-----------|-----------|--------|----------|----------|
| GSOC | 0.998 | 0.964 | 0.980 | 0.998 |
| GMG | 0.915 | 0.995 | 0.952 | 0.994 |
| MOG | 0.869 | 0.354 | 0.492 | 0.964 |

### Shadow Cubicle Sequence
| Algorithm | Precision | Recall | F1-Score | Accuracy |
|-----------|-----------|--------|----------|----------|
| GSOC | 0.522 | 0.814 | 0.513 | 0.991 |
| MOG | 0.662 | 0.465 | 0.414 | 0.990 |
| GMG | 0.302 | 0.541 | 0.280 | 0.984 |

## Troubleshooting

### Common Issues

1. **OpenCV Import Error**
   ```bash
   pip uninstall opencv-python opencv-contrib-python
   pip install opencv-python opencv-contrib-python
   ```

2. **C++ Compilation Error**
   - Ensure OpenCV is properly installed and linked
   - Check CMake configuration
   - Verify compiler compatibility

3. **Dataset Path Issues**
   - Ensure dataset follows Change Detection 2014 format
   - Check file permissions
   - Verify image file extensions (.jpg for input, .png for ground truth)

4. **Memory Issues**
   - Reduce image resolution for large datasets
   - Process sequences in smaller batches
   - Monitor system memory usage

## Contributing

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Add tests if applicable
5. Submit a pull request

## License

This project is open source. Please check the license file for details.

## References

- [OpenCV Background Subtraction Documentation](https://docs.opencv.org/master/d1/dc5/tutorial_background_subtraction.html)
- [Change Detection 2014 Dataset](http://changedetection.net/)
- [Background Subtraction Algorithms Survey](https://ieeexplore.ieee.org/document/6854312)

## Blog Post

For additional implementation details and analysis, see: https://philippeheitzmann.com/2022/01/tracking-objects-using-opencv-background-subtraction/