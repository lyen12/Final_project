# Final_project_for_EE520
Linda Yen

Goal
===
The goal of this project was to incorporate what we have learned about C++, Elma, and ENVIRO to create a working system.

Ideas
===
My original implementation was a Tetris like environment, but instead of pieces, you could control a block with the 'a','d', and 's' keys.
This would control the left, right, and down movements respectively. Once the block hit the bottom, a new block would be
added at the top of the grid, and control would be transferred to that block. I then decided to make this into more of a game, by removing
the grid structure and changing control to drop the block when the spacebar is pressed. The block would bounce left and right at a fast speed
and the Player would try to stack the blocks to reach a certain height.

Key Challenges
===
- Setting keyboard control to only the most recently added block. I was able to do this by addind the id info of the Block emitting then event.
  Then I added an if-statement in each Watch statement to only perform the changes if the id matches that block.
- Stopping the block at the position the spacebar was pressed. Since I was using apply_force to make the block bounce between the Bumpers, I
  used the Teleport method to stop the block and place it at the position the block was at when the spacebar was pressed.
- Add a block after the block touches the bottom. To address this, I added a counter to give some time for the block to fall to the bottom 
  before the next block appears.
- Removing all agents after the Reset button is pressed. To do this, I captured every existing agent id into a vector by sending the id as an 
  event and watching for the event in win_message.cc. Then win_message.cc watches for the Reset event and removes every agent id stored in the 
  existing_agents vector.
- 

Set Up Instructions
===
- Clone this repository:
`https://github.com/lyen12/Final_project.git

-Start a Docker container with ENVIRO pre-loaded into it by running:

```bash
docker run -p80:80 -p8765:8765 -v $PWD:/source -it klavins/enviro:alpha bash
esm start
```

The above commands do the following:

- The `-p80:80 option maps *port* 80 from the Docker container to ports on your host computer.  
    > If you have a MAC: This should allow you to go to http://localhost with your web browser and see the ENVIRO client. It should say "Error: Failed 
      to fetch. Is the server running?" at this point. 
    > If you are using Docker Toolbox on Windows: Open Virtual Box Manager -> Default (right click -> settings) -> Network -> Advanced -> Port Forwarding
      and set the rules as below. This should allow you to go to 192.168.99.100 in your web browser and see the ENVIRO client. 
	Name   | TCP | Host IP   | Host Port| Guest IP       | Guest Port
	Rule 1 | TCP | 0.0.0.0   | 80       | 192.168.99.100 | 80
	Rule 2 | TCP | 0.0.0.0   | 8765     |                | 8765
        Rule 3 | TCP | 127.0.0.1 | 51058    |                | 22

- The `-p8765:8765` option allows the ENVIRO client to communicate with the `enviro` server (not yet running) via a *WebSocket*.

- The command `esm start` uses the <u>e</u>nviro <u>s</u>etup <u>m</u>anager to start a web server from which your browser can access the ENVRIO client. 

- Make the project and start the enviro sever as follows.
```bash
make
enviro
```

- Go back to your web browser (either http://localhost or 192.168.99.100) and you should see a block bouncing left and right between two red bumpers. 

How to Play the Game
===
- The goal of the game is to stack Blocks until you reach the Red Finish Line. A "You Win!" message will appear when you reach the finish line. 

Acknowledgements
===
- Lectures from https://github.com/klavins/EEP520-W20
- Info on ENVIRO: https://github.com/klavinslab/enviro
- Info on Elma: http://klavinslab.org/elma/index.html

