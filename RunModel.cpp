#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>

using namespace std;

int main(int argc, char* argv[]) {
    string videoPath = "video.mp4";
    if (argc > 1) {
        videoPath = argv[1];
    }

    ifstream promptFile("prompt.txt");
    if (!promptFile) {
        cerr << "Failed to open prompt.txt\n";
        return 1;
    }

    ostringstream buffer;
    buffer << promptFile.rdbuf();
    string prompt = buffer.str();

    if (!prompt.empty() && prompt.back() == '\n') {
        prompt.pop_back();
    }

    string command =
        "python video_audio_demo.py "
        "--model_path /workspace/test/VITA-1.5 "
        "--video_path \"" + videoPath + "\" "
        "--model_type qwen2p5_instruct "
        "--conv_mode qwen2p5_instruct "
        "--question \"" + prompt + "\" "
        "--vision_tower_path /workspace/test/InternViT "
        "--audio_encoder_path /workspace/test/VITA-1.5/audio-encoder-Qwen2-7B-1107-weight-base-11wh-tunning "
        "--device auto";

    int result = system(command.c_str());

    return result;
}

