public class test {
	static int cur_x;
	static int cur_y;
	static int maze[][] = new int[16][16];


	public static int minimize(int left, int right, int up, int down) {
	  int dir[] = {left, right, up, down};
	  int min = 256;
	  for (int i=0; i<4; i++) {
	    if (dir[i] < min) {
	      min = dir[i];
	    }
	  }
	  return min;
	}


	public static void orderNeighbors() {
		int N,S,E,W;
  		if (cur_x == 0) {
		     N = maze[cur_y-1][cur_x];
		     S = maze[cur_y+1][cur_x];
		     E = maze[cur_y][cur_x+1];
		     W = 258;
		  }
		  else if (cur_x == 15) {
		     N = maze[cur_y-1][cur_x];
		     S = maze[cur_y+1][cur_x];
		     E = 258;
		     W = maze[cur_y][cur_x-1];
		  }
		  else if (cur_y == 0) {
		     N = 258;
		     S = maze[cur_y+1][cur_x];
		     E = maze[cur_y][cur_x+1];
		     W = maze[cur_y][cur_x-1];
		  }
		  else if (cur_y == 15) {
		     N = maze[cur_y-1][cur_x];
		     S = 258;
		     E = maze[cur_y][cur_x+1];
		     W = maze[cur_y][cur_x-1];
		  }
		  else {
		     N = maze[cur_y-1][cur_x];
		     S = maze[cur_y+1][cur_x];
		     E = maze[cur_y][cur_x+1];
		     W = maze[cur_y][cur_x-1];
		  }
		int directions[] = {N,S,E,W};
	  char sequenced[] = new char[4];
	  int temp = 0;
	  
	  System.out.print(N);
	  System.out.print(E);
	  System.out.print(S);
	  System.out.println(W);	  

	  for (int i=0; i<4; i++) {
	    for (int j=i+1; j<4; j++) {
	      if (directions[j] < directions[i]) {
	        temp = directions[i];
	        directions[i] = directions[j];
	        directions[j] = temp;
	      }
	    }
	  }
  
	  
	  for (int k=0; k<4; k++) {
	    if (directions[k] == N) {
	      sequenced[k] = 'N';
	      N = 257;
	    }
	    else if (directions[k] == S) {
	      sequenced[k] = 'S';
	      S = 257;
	    }
	    else if (directions[k] == E) {
	      sequenced[k] = 'E';
	      E = 257;
	    }
	    else if (directions[k] == W) {
	      sequenced[k] = 'W';
	      W = 257;
	    }
	  }

	  System.out.print(sequenced[0]);
	  System.out.print(sequenced[1]);
	  System.out.print(sequenced[2]);
	  System.out.println(sequenced[3]);
	}
	public static int manhattanDist(int x1, int y1, int x2, int y2) {
	  return Math.abs(x1-x2) + Math.abs(y1-y2);
	}

	public static void initializeGrid() {
	  for (int i=0; i<16; i++) {
	    for (int j=0; j<16; j++) {
	      maze[i][j] = minimize(manhattanDist(i, j, 7, 7), manhattanDist(i, j, 7, 8), manhattanDist(i, j, 8, 7), manhattanDist(i, j, 8, 8));
	    }
	  }

	}
	public static void printGrid() {
		for (int i=0; i<16; i++) {
			for (int j =0; j<16; j++) {
				if (maze[i][j] > 9) {
					System.out.print(maze[i][j] + " ");
				}
				else {
					System.out.print(maze[i][j] + "  ");
				}
			}
			System.out.print("\n");
		}
	}
	public static void main(String[] args) {
		initializeGrid();
		cur_x = 1;
		cur_y = 14;
		maze[cur_y][cur_x] = 19;
		printGrid();
		orderNeighbors();
	}

}