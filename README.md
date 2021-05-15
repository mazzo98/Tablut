# Team Angio - Tablut

This is our implementation of an intelligent agent developed to play Tablut. It was built to take part in the 2021 Tablut Challenge of the Fundamentals of AI course held by prof. Paola Mello and prof. Federico Chesani (University of Bologna).

The competition required us to stick to Ashton rules ([learn more here](https://www.heroicage.org/issues/13/ashton.php)) and Andrea Galassi' s server for communication with players and maintaining the game state. The server is available [this repository](https://github.com/AGalassi/TablutCompetition).

## A brief description
- Bitboards: the game state is implemented using bitboards in order to speedup move inference;
- Monte Carlo Tree Search: we aimed for the stars trying to code something like [AlphaZero](https://en.wikipedia.org/wiki/AlphaZero).  Thus, we implemented a Monte Carlo Tree Search, but we couldn't deal with the Neural Network part due to very tight schedules. Hopefully, we'll do it in the future! 

## How to run
You just need to clone this repository, install the requirements, and set up the environment:
```
$ git clone https://github.com/mazzo98/Tablut
```
```
$ cd Tablut
```
```
$ pip3 install -r requirements.txt
```
```
$ sudo setup.sh
```
Then you simply launch the program with:
```
 $ ./runmyplayer.sh <white|black> timeout ip_server
```
And last but not least: HAVE FUN!

## Team Angio

- [Jasmin De Cecco](https://github.com/jasmindc) 
- [Matteo Di Lorenzi](https://github.com/m-dilorenzi)
- [Lorenzo Magnanelli](https://github.com/rolench)
- [Mattia Mazzoli THE LEGEND](https://github.com/mazzo98)
