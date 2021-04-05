# Visn* AA Engine
*To be renamed
## Motive
There hasn't been a satisfactory Ace Attorney fancase maker in some time. PyWright relies on ancient Python 2.7 code and is no longer maintained, AAOnline is not quite extensible enough, and objection.lol is not remotely powerful enough to be a true recreation of the first three Ace Attorney games' (and perhaps arguably AJ:AA's as well) engine. This hopes to solve that.
## Dependencies
You'll need a version of Love2D of at least 11.0 installed on your local machine. (for now -- Love2D lets you bundle its executable with releases, so this won't be an issue for long)
## Running the example case
Navigate to the root directory of the repository from a command line and enter `love . example`. It should work fine from there. 

# Usage and scripting guide
(Wiki in progress, consult this for now)
I'm not great at writing documentation -- feel free to submit an improvement via pull request or talk to me over Discord or Twitter!
## Creating a case
Some default assets for basic gameplay are included by default, so in many cases all you need to do is the following:
- In the main folder for Visn, there's a `games/` folder. Create a new folder with a name of your choosing in that `games/` folder.
- In your new folder, make a new folder called `script`. In this folder, make a new text file and entitle it `main.txt`. This is the script file that will be first loaded when you launch Visn.
- Other script files can be created and loaded in individual scripts via the `script` command.
## Very brief example script:
`main.txt`:
```
script scene
```

`scene.txt`:
```
bg defense
fg defense
char Phoenix document {
    Some text.
    {c default}Some {c emphasis}highlighted{c default} text.
}
```
## Asset management
### Directory setup
Your game's directory setup will look something like this. Directories you don't use can be removed with no risk.
```
(your game's name)
├── assets
│   ├── bg
│   ├── char
        ├── character-1
        ├── ...
        └── last-character
│   ├── fg
│   ├── font
│   ├── sfx
│   ├── music
│   └── ui
├── script
└── game_conf.lua
```
Anything without a file extension (e.g., `.lua`) is a (sub-)directory. The folders work like so:
- `assets`: Contains image and sound data for your game.
    - `bg`, `fg`, `ui`: Contains image assets for backgrounds, foregrounds, and UI elements respectively.
    - `char`: Contains folders for each character that appears in your game. These folders contain the sprites in the form of image assets and some additional information about each character.
    - Image assets consist of two files: an image with a `.png` extension, and an optional `.txt` file with the same base name as the image file. If the image asset is animated, it should be laid out in a grid format where each cell has a size of 256x192 pixels (the size of each of the DS's screens). Animated images must include the `.txt` file, as it describes the size and layout of the grid, as well as several other animation properties. These are described in the Art and animation subheader of the next section.
    - `font`: If desired, contains an image file that overrides the default font used by the engine. The format for this font image can be found [here](https://love2d.org/wiki/ImageFontFormat).
    - `sfx`: Contains sound effects in the form of `.mp3`, `.wav`, `.flac`, or `.ogg` files. Music and particularly long sounds (say, longer than 15 or 20 seconds) should not be used here, and should instead go into `music`.
    - `music`: See `sfx`: these are longer sound files that are used largely for background music.
- `script`: Contains script files in the form of `.txt` files. `main.txt` will always be the first file loaded by the engine, and your game will not run without one.


## Commands and formatting tags
### Implemented
#### Art and animation
These commands search the directories both in your game's and the prepackaged assets (if not found in your game) directories for their respective files (with no extensions). E.g., `sfx bam` would search first `(visn root)/games/your-game/assets/sfx` for a file like `bam.mp3`, and if not found, `(visn root)/assets/sfx`. 
- `fg image` and `bg image`: Set foreground and background images to `assets/fg/image.png` or `assets/bg/image.png`, respectively. These can be animated (see Asset management).
#### Characters and speakers
These commands alter which character is displayed or speaking, or introduce dialogue blocks.
- `char character-folder emotion`, `char character-folder`, or `char`: Set the current speaker and animated character to the character whose information is stored in `character-folder` to the emotion specified by `emotion`. Omit `(blink)` or `(talk)` from `emotion`, this is handled by the engine.
    - ***Important***: Lines that start with `char` should end in an opening curly brace (`{`) if they begin a section of dialogue. Lines inside the braces will be treated as dialogue and not engine scripting, and each line will get its own textbox. It is sometimes necessary to split long lines (generally >75 characters) over multiple textboxes. See the example script to see how this works in practice.
    - If `emotion` is omitted, the engine assumes it to be `normal`. If the line just consists of `char {`, the engine hides the nametag and does not alter the current speaker.

#### Text formatting
All of these tags occur within dialogue blocks, not plain scripting lines. They affect how text is rendered or make things happen at certain points of script lines. 

- `{c}`: Colors text up until the next `{c}` tag as the specified color. If this tag is used, the line it's used on should start with `{c default}`.
    - Takes arguments as either `{c r g b}` or `{c color}` where `r`, `g`, and `b` are integers from 0-255 or `color` is one of the default colors. The default colors are:
        - `emphasis` or `red`: The color used to highlight important text or to start cross-examinations in the Ace Attorney games.
        - `think`, `thinking`, or `blue`: The color used when characters are thinking to themselves in the Ace Attorney games.
        - `green`: The color used when characters begin in a new location or during cross-examinations in the Ace Attorney games.
        - `default` or `white`: The default color used for text in the Ace Attorney games. Must be used at the beginning of a line if the first word(s) of that line don't have a different color.


### Unimplemented


# Current issues
- Bug where character switching can sometimes cause dialogue to get stopped at the first letter

# Development Checklist
## Animation features
- [x] looping animations
- [x] talking and blinking animations
- [ ] follow-up animations
- [ ] one-shot animations (very easy implementation)
- [ ] fading
## Gameplay features
- [ ] Court Record
    - [ ] Add evidence
    - [ ] Highlight evidence in dialogue
    - [ ] Menu screen
- [ ] Investigation segments
    - [ ] Examine
    - [ ] Move
    - [ ] Talk
    - [ ] Present
- [ ] Cross examination
    - [ ] Psyche-Lock segments
- [ ] Penalties
- [ ] Game over
## Dialogue/scripting features
- [x] character specification (`char`)
- [x] animation specification (`char [character] [animation]`)
- [x] background/foreground switching (`bg` and `fg`)
- [x] animation switching
    - I don't like the way it's done -- want to be able to switch inline via `{emotion}` or `{emo}` tags
- [x] script switching (`script`)
- [ ] text highlighting
    - Implementation of `{c}` tags like 80% done
    - Very easy addition of named colors (thinking, emphasis, green, etc.)
- [ ] Flash, shake, etc
- [ ] Inline background, foreground switching
- [ ] have nametag different from speaking character
- [ ] separate out speaking and displayed character with less complicated code
- [ ] Highlight evidence in dialogue
- [ ] Flags, jumps, named sections
## QoL stuff
- [ ] Stop talking animation when speaking character is thinking
- [ ] Figure out how in God's name the AA devs spaced out the nametags
    - I seriously don't get how they did this
    - [The `e`s in Phoenix's name are like 3 pixels wide, on Gumshoe's they're like 2](https://i.imgur.com/oFlrmPM.png), I can't figure out how they did it
    - Please DM me on Discord (`@lynne#6968`) or Twitter (`@_lynnux`) or something if you figure it out I'm losing my marbles