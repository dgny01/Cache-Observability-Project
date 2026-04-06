CXX = g++
CXXFLAGS = -O3 -Iinclude -std=c++17
TARGET = build/cache_analyzer


all:
	@mkdir -p build
	$(CXX) $(CXXFLAGS) src/main.cpp src/analyzer.cpp -o $(TARGET)


clean:
	rm -rf build/