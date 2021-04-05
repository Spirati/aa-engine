# Untitled AA Engine
## Motive
There hasn't been a satisfactory Ace Attorney fancase maker in some time. PyWright relies on ancient Python 2.7 code and is no longer maintained, AAOnline is not quite extensible enough, and objection.lol is not remotely powerful enough to be a true recreation of the first three Ace Attorney games' (and perhaps arguably AJ:AA's as well) engine. This hopes to solve that.
## Dependencies
You'll need a version of Love2D of at least 11.0 installed on your local machine. (for now -- Love2D lets you bundle its executable with releases, so this won't be an issue for long)
## Running the example case
Navigate to the root directory of the repository from a command line and enter `love . example`. It should work fine from there. 

# Development Checklist
## Animation features
- [x] looping animations
- [x] talking and blinking animations
- [ ] follow-up animations
- [ ] one-shot animations (very easy implementation)
- [ ] fading
## Gameplay features
- [ ] Investigation segments
- [ ] Cross examination
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
- [ ] Flags, jumps, named sections
## QoL stuff
- [ ] Stop talking animation when speaking character is thinking
- [ ] Figure out how in God's name the AA devs spaced out the nametags
    - I seriously don't get how they did this
    - The `e`s in Edgeworth's name are like 5 pixels wide, on Gumshoe's they're like 4, I can't figure out how they did it
    - Please DM me on Discord (`@lynne#6968`) or Twitter (`@_lynnux`) or something if you figure it out I'm losing my marbles