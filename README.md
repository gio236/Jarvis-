# JARVIS - AI Voice Assistant

GIARVIS is a C-based voice assistant that integrates speech recognition, AI-powered responses, and text-to-speech functionality. The assistant responds to the wake word "jarvis" and can perform various tasks including weather queries, music playback, and general conversation.

## Features

- **Voice Recognition**: Real-time speech recognition using Vosk API
- **AI Integration**: Powered by Groq's Llama 4 Scout model for intelligent responses
- **Text-to-Speech**: Italian voice synthesis using eSpeak
- **Music Control**: Automatic music playback when requested
- **Weather Information**: Weather queries for Bologna, Italy
- **System Control**: Shutdown command functionality

## Prerequisites

### Required Libraries
- **Vosk**: Speech recognition library (vosk_api.h + libvosk.so)
- **Jansson**: JSON parsing library
- **eSpeak**: Text-to-speech synthesis
- **aplay**: Audio playbook utility
- **jq**: JSON processor (for parsing API responses)
- **curl**: HTTP client
- **mpv**: Media player

### System Requirements
- Linux-based operating system
- Microphone for audio input
- Audio output device
- Internet connection for AI API calls

## Installation

### 1. Install Dependencies

**Ubuntu/Debian:**
```bash
sudo apt update
sudo apt install espeak aplay jq curl mpv build-essential
```

**For Vosk:**
- Download Vosk C API from [https://alphacephei.com/vosk/](https://alphacephei.com/vosk/)
- You need these specific files:
  - `vosk_api.h` (header file)
  - `libvosk.so` (shared library)
- Download the Italian model `vosk-model-it-0.22`
- Extract model to your project directory
- Place `vosk_api.h` and `libvosk.so` in your project directory

**For Jansson:**
```bash
sudo apt install libjansson-dev
```

### 2. Setup API Key
Replace `YOUR API KEY` in the source code with your actual Groq API key:
```c
"-H \"Authorization: Bearer YOUR_GROQ_API_KEY\" "
```

### 3. Compilation
```bash
export LD_LIBRARY_PATH=~/vosk
gcc test.c -o test -I. -L. -lvosk -ljansson
```

## Usage

### Running the Assistant
```bash
export LD_LIBRARY_PATH=~/vosk
arecord -f S16_LE -r 16000 -c 1 | ./test
```

### Voice Commands
- **Wake Word**: Say "jarvis" at the end of the prhase to activate the assistant
- **Weather**: Ask about weather conditions in Bologna
- **Music**: Request music playback with commands like "metti musica"
- **Shutdown**: Say shutdown commands to terminate the assistant
- **General Queries**: Ask any question for AI-powered responses

## Configuration

### System Prompt
The assistant is configured with a specific personality and behavior:
- Name: GIARVIS (responds to "jarvis")
- Owner: Gioele
- Language: Italian
- Response Style: Concise and helpful
- Special Commands: Music playback and system shutdown

### Audio Settings
- **Sample Rate**: 16kHz
- **Format**: 16-bit Little Endian
- **Channels**: Mono
- **Voice**: Italian female voice (it+f3)
- **Speech Rate**: 110 words per minute

## File Structure
```
project/
├── test.c              # Main source code
├── test                # Compiled executable
├── vosk_api.h          # Vosk header file
├── libvosk.so          # Vosk shared library
├── vosk-model-it-0.22/ # Italian speech recognition model
├── output.txt          # Temporary file for AI responses
└── ~/Downloads/musica/ # Music directory (*.mp3 files)
```

## How It Works

1. **Audio Capture**: The program captures audio from microphone using `arecord`
2. **Speech Recognition**: Vosk processes audio stream and converts speech to text
3. **Wake Word Detection**: Monitors for "jarvis" in the recognized text
4. **AI Processing**: Sends recognized text to Groq API with system prompt
5. **Response Generation**: Receives AI response and saves to output file
6. **Text-to-Speech**: Converts response to speech using eSpeak
7. **Action Execution**: Processes special commands (music, shutdown)

## Special Commands

### Music Playback
When the AI response contains `{musica:avvio}`, the system automatically plays music files from `~/Downloads/musica/`

### System Shutdown
When the AI response contains `{spegnimento:avvio}`, the assistant terminates

### Weather Queries
Weather information is fetched from `wttr.in/Bologna` with custom formatting

## API Integration

The assistant uses Groq's API with the following configuration:
- **Model**: meta-llama/llama-4-scout-17b-16e-instruct
- **Endpoint**: https://api.groq.com/openai/v1/chat/completions
- **Content-Type**: application/json
- **Authentication**: Bearer token required

## Troubleshooting

### Common Issues
1. **Audio Input Problems**: Check microphone permissions and ALSA configuration
2. **Vosk Model Not Found**: Ensure the Italian model is in the correct directory
3. **API Authentication**: Verify your Groq API key is valid and properly configured
4. **Library Dependencies**: Make sure all required libraries are installed

### Debug Mode
The program outputs various debug information including:
- Current timestamp
- System prompt
- Recognized text
- Full curl command
- AI response

## Contributing

This is a personal project for voice assistant functionality. Feel free to fork and modify according to your needs.

## License

This project is for educational and personal use. Please respect the terms of service of all integrated APIs and libraries.

## Language Customization

### Switching to English Version

If you want to switch to English version, you can do this:

1. **Change the Vosk model**: Replace the Italian model with an English one in your project directory
   - Download an English model like `vosk-model-en-us-0.22` from [Vosk Models](https://alphacephei.com/vosk/models.html)
   - Update the model path in the code:
   ```c
   VoskModel *model = vosk_model_new("vosk-model-en-us-0.22");
   ```

2. **Replace the system prompt**: Modify the prompt variable to use English instructions
   - Change the Italian instructions to English equivalents
   - Update weather location if needed (replace Bologna with your city)

3. **Replace text-to-speech with English mode**: Update the eSpeak voice settings
   - Change from Italian voice `it+f3` to English voice like `en+f3`
   - Update both in the `speak()` function and the curl command:
   ```c
   "espeak -v en+f3 -s 110"
   ```

## Credits

- **Vosk**: Speech recognition
- **Groq**: AI language model
- **eSpeak**: Text-to-speech synthesis
- **Jansson**: JSON parsing
