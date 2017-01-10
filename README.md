# sLap Counter

The sLap Counter is an intelligent, personal poolside lap counter with smartphone integration.

## Installation

- Install [Git](https://git-scm.com/book/en/v2/Getting-Started-Installing-Git)

- Install platformio (run in terminal)

```bash
python -c "$(curl -fsSL https://raw.githubusercontent.com/platformio/platformio/master/scripts/get-platformio.py)"
```

- Clone and enter repository

```bash
git clone https://github.com/alexozer/slapcounter.git && cd slapcounter
```

## Uploading to sLapCounter

While you're in the slapcounter directory:

```bash
platformio run -t upload
```

The first upload may take a little bit longer as dependencies are installed or compiled.

## Updating sLapCounter software

While you're in the slapcounter directory:

```bash
git pull
```
