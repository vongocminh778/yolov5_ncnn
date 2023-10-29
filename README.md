# Install Ncnn
```
git clone https://github.com/Tencent/ncnn.git
cd ncnn
git submodule update --init
sudo apt install build-essential git cmake libprotobuf-dev protobuf-compiler libvulkan-dev vulkan-utils libopencv-dev
wget https://sdk.lunarg.com/sdk/download/1.2.189.0/linux/vulkansdk-linux-x86_64-1.2.189.0.tar.gz?Human=true -O vulkansdk-linux-x86_64-1.2.189.0.tar.gz
tar -xf vulkansdk-linux-x86_64-1.2.189.0.tar.gz
export VULKAN_SDK=$(pwd)/1.2.189.0/x86_64
cd ncnn
mkdir -p build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_OSX_ARCHITECTURES="x86_64" -DNCNN_VULKAN=ON -DNCNN_BUILD_EXAMPLES=ON -DNCNN_BUILD_TOOLS=ON -DNCNN_DISABLE_RTTI=OFF ..
make -j$(nproc)
```
# Convert yolov5 -> onnx -> ncnn

# Communication PC -> Arduino
sudo apt-get update
sudo apt-get install libserialport0 libserialport-dev
