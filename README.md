<a href="https://developer.microsoft.com">![Microsoft](https://img.shields.io/badge/Microsoft-666666?style=for-the-badge&logo=microsoft&logoColor=white)</a>
<a href="https://winworldpc.com/product/microsoft-c-c/7x">![C language](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)</a>

# Video Overlay for DOS

This project provides a live video-stream overlay for DOS applications using the New Media Graphics Super VideoWindows board. The solution was originally developed in 1994 and allows for genlocking a live NTSC video source.

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Configuration](#configuration)
- [Compilation](#compilation)
- [License](#license)

## Overview

The Museum Video Overlay for DOS project enables the overlay of live video streams onto DOS applications. It utilizes the New Media Graphics Super VideoWindows board to achieve this functionality. The project includes source code, configuration files, and build scripts necessary to compile and run the solution.

## Features

- Overlay live NTSC video onto DOS applications.
- Configurable video window dimensions.
- Error handling for video initialization and configuration.
- Support for various video and audio settings.

## Requirements

- DOS operating system.
- New Media Graphics Super VideoWindows board.
- Microsoft C/C++ Compiler Version 8.00c.
- Microsoft Segmented Executable Linker Version 5.60.

## Installation

1. Clone the repository to your local machine:
    ```sh
    git clone https://github.com/yourusername/museum-video-overlay-for-DOS.git
    ```
2. Navigate to the `src` directory:
    ```sh
    cd museum-video-overlay-for-DOS/src
    ```

## Usage

To run the video overlay program, use the following command:
```sh
VSET <left> <top> <right> <bottom>
```

## Configuration

The video settings are configured in the VIDEO.INI file located in the src directory. Below is an example configuration:
```markdown
[VideoUnits]
SVW=SVW

[SVW]
IOaddr=0xAD6
MemAddr=0xE00000

[Sources]
Source1=Unknown

[Source1]
Signal=NTSC
Active=YES
VideoOut=SVW,v1
AudioOut=SVW,a1

[System]
DefaultSource=Source1
```

## Compilation

To compile the project, use the provided batch script CC.BAT:

Ensure the paths to the Microsoft C/C++ Compiler and Linker are correctly set in the batch script.
Run the batch script:

    ```sh
    CC.BAT
    ```

## Contact
<a href="mailto:Ronald.Redmer@gmail.com">![Gmail](https://img.shields.io/badge/Gmail-D14836?style=for-the-badge&logo=gmail&logoColor=white)</a>
<a href="https://signal.link/call/#key=kmxm-qmqs-zcxx-znxm-tbpm-fgpf-xxzt-gsdh">![Signal](https://img.shields.io/badge/Signal-3A76F0?style=for-the-badge&logo=signal&logoColor=white)</a>
<a href="https://t.me/RonaldRedmer">![Telegram](https://img.shields.io/badge/Telegram-2CA5E0?style=for-the-badge&logo=telegram&logoColor=white)</a>
<a href="https://wa.me/12484972761">![WhatsApp](https://img.shields.io/badge/WhatsApp-25D366?style=for-the-badge&logo=WhatsApp&logoColor=white)</a>

### Follow
<a href="https://bsky.app/profile/rredmer.bsky.social">![BlueSky](https://img.shields.io/badge/Bluesky-0285FF?logo=bluesky&logoColor=fff&style=for-the-badge)</a>
<a href="https://devrant.com/users/rredmer">![DevRant](https://img.shields.io/badge/devRant-F99A66?style=for-the-badge&logo=devrant&logoColor=white)</a>
<a href="https://discordapp.com/users/RedZone">![Discord](https://img.shields.io/badge/Discord-5865F2?style=for-the-badge&logo=discord&logoColor=white)</a>
<a href="https://matrix.to/#/@ronaldredmer:matrix.org">![Element](https://img.shields.io/badge/Element-0DBD8B?style=for-the-badge&logo=element&logoColor=white)</a>
<a href="https://www.kaggle.com/ronredmer">![Kaggle](https://img.shields.io/badge/Kaggle-20BEFF?style=for-the-badge&logo=Kaggle&logoColor=white)</a>
<a href="https://www.linkedin.com/in/rredmer/">![LinkIn Profile](https://img.shields.io/badge/LinkedIn-0077B5?style=for-the-badge&logo=linkedin&logoColor=white)</a>
<a href="https://mastodon.social/@RonaldRedmer">![Mastodon](https://img.shields.io/badge/Mastodon-6364FF?style=for-the-badge&logo=Mastodon&logoColor=white)</a>
<a href="https://www.quora.com/profile/Ron-Redmer">![Quora Profile](https://img.shields.io/badge/Quora-%23B92B27.svg?&style=for-the-badge&logo=Quora&logoColor=white)</a>
<a href="https://www.reddit.com/user/RonaldRedmer/">![Reddit](https://img.shields.io/badge/Reddit-FF4500?style=for-the-badge&logo=reddit&logoColor=white)</a>
<a href="https://stackoverflow.com/users/29130217/ron-redmer">![Stack Overflow](https://img.shields.io/badge/Stack_Overflow-FE7A16?style=for-the-badge&logo=stack-overflow&logoColor=white)</a>
<a href="https://www.tumblr.com/blog/ronaldredmer">![Tumblr](https://img.shields.io/badge/Tumblr-%2336465D.svg?&style=for-the-badge&logo=Tumblr&logoColor=white)</a>
<a href="https://www.twitch.tv/ronaldredmer">![Twitch](https://img.shields.io/badge/Twitch-9146FF?style=for-the-badge&logo=twitch&logoColor=white)</a>
<a href="https://www.youtube.com/@RonaldRedmer">![YouTube](https://img.shields.io/badge/YouTube-FF0000?style=for-the-badge&logo=youtube&logoColor=white)</a>

<a href="https://github.com/rredmer">![Github](https://img.shields.io/badge/GitHub-100000?style=for-the-badge&logo=github&logoColor=white)</a>
<a href="https://dev.to/rredmer">![Dev.to](https://img.shields.io/badge/dev.to-0A0A0A?style=for-the-badge&logo=devdotto&logoColor=white)</a>
<a href="https://medium.com/@ronald.redmer">![Medium](https://img.shields.io/badge/Medium-12100E?style=for-the-badge&logo=medium&logoColor=white)</a>
<a href="https://x.com/ron_redmer">![X (formerly Twitter) Follow](https://img.shields.io/twitter/follow/ron_redmer)</a>

### Sponsor
<a href="https://github.com/sponsors/rredmer">![Github Sponsor](https://img.shields.io/badge/sponsor-30363D?style=for-the-badge&logo=GitHub-Sponsors&logoColor=#white)</a>
<a href="https://buymeacoffee.com/rredmer">![Buy me a cofee](https://img.shields.io/badge/Buy_Me_A_Coffee-FFDD00?style=for-the-badge&logo=buy-me-a-coffee&logoColor=black)</a>
<a href="https://patreon.com/TechnologyPlayground">![Patreon](https://img.shields.io/badge/Patreon-F96854?style=for-the-badge&logo=patreon&logoColor=white)</a>
<a href="https://paypal.me/RonaldRedmer">![PayPal](https://img.shields.io/badge/PayPal-00457C?style=for-the-badge&logo=paypal&logoColor=white)</a>
<a href="https://donate.stripe.com/9AQg0G6on55a1pK288">![Stripe](https://img.shields.io/badge/Stripe-626CD9?style=for-the-badge&logo=Stripe&logoColor=white)</a>

### Web
<a href="https://ronaldredmer.com">![Ronald Redmer Portfolio](https://img.shields.io/badge/Ronald%20Redmer%20Portfolio-blue?style=for-the-badge)</a>
<a href="https://a1si.com">![A1 Systems Integrators LLC](https://img.shields.io/badge/A1%20Systems%20Integrators-blue?style=for-the-badge)</a>
<a href="https://techproductsgroup.com">![Technical Products Group](https://img.shields.io/badge/Technical%20Products%20Group-blue?style=for-the-badge)</a>

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.
