## Welcome to the IoT-LAB training resources

This repository is forked from https://github.com/iot-lab/iot-lab-training and
adapted for IESE5_UE_IoT Grenoble Polytech course.

### Description

This repository contains the Jupyter Notebooks available at
https://labs.iot-lab.info and used ad training resources to easily start using
the IoT-LAB testbed. Some of the exercises have been adapted to be ran on locally
available hardware, they can be found under **riot/polytech**.

Other exercises available are best followed directly through https://labs.iot-lab.info/.

### Getting started

We recommend that you follow the `start.ipynb` notebook to learn how to use
Jupyter Notebooks.

- Notebooks in **riot** will let you discover the [RIOT](https://riot-os.org)
  operating system:
  - **riot/basics** contains exercises on basics features of RIOT
  - **riot/networking** contains networking exercises (802.15.4, IPv6, UDP, CoAP
    and LwM2M)
  - **riot/lorawan** contains exercises on LoRaWAN LPWAN networks
  - **riot/security** contains exercises on security aspects for IoT (hash,
    crypto, DTLS and OTA)
  - **riot/polytech** contains a selection of exercises adapted to be ran on
  `native`, Nucleo-f446re and LoRa-E5-Dev.
- Notebooks in **contiki-ng** contains exercises to discover the
  [Contiki-NG](https://www.contiki-ng.org/) operating system
- Notebooks in **testbed** shows advanced features of the IoT-LAB testbed:
  - for measuring power consumption on IoT-LAB M3 devices
  - for sniffing radio paquets between IoT-LAB M3 devices

### Run Locally

1. Install required tooling for RIOT, see [Getting Started](https://doc.riot-os.org/getting-started.html).


_NOTE_: `openocd > v0.11.0` is required to flash LoRa-E5-dev, this is installed by
default if on Ubuntu > 21.04. Otherwise `openocd` will need to be [installed from
source](https://github.com/openocd-org/openocd).

2. Clone this repository:

  ```
  $ git clone --recursive https://github.com/fjmolinas/iot-lab-training -b polytech
  ```

3. [Install Jupyter Lab](https://jupyterlab.readthedocs.io/en/stable/getting_started/installation.html#)

4. Start a local JupyterLab server

  ```
  $ cd iot-lab-training
  $ jupyter lab
  ```

5. Connect to JupyterLab at http://localhost:8888/lab

You can then edit the notebooks in your browser. Make sure to clear all the outputs before
committing your changes.

#### Extra Setup

1. Flash devices without being `sudo` (Ubuntu users):

  ```
  sudo usermod -a -G dialout $USER
  sudo usermod -a -G plugdev $USER
  ```

  logout, and log back in.
