A classic terminal-based Minesweeper game written in C. This project was developed as a programming exercise to practice 2D arrays, recursion, and File I/O in a Linux environment.

🚀 Features
    -Recursive Reveal Algorithm: Automatically clears empty areas when a blank cell is opened using the Flood Fill logic.

    -Color-Coded Interface: Visual feedback using ANSI escape codes inspired by the original Windows Minesweeper colors.

    -Game Modes: Supports opening cells (O), flagging potential mines (F), and unflagging (U).

    -Match History: Automatically logs game results, including win/loss status, final map layout, and total playtime, into a result.txt file.

    -Input Sanitization: Robust handling of invalid coordinates and data types to prevent program crashes.

🎮 How to Play
    -Open a Cell: Enter coordinates followed by o (e.g., 5 5 o).

    -Flag a Mine: Enter coordinates followed by f (e.g., 3 2 f) to mark a suspected mine.

    -Unflag: Enter coordinates followed by u to remove a flag.

    -Win Condition: Open all cells that do not contain a mine.

    -Lose Condition: Opening a cell with a mine (B) ends the game immediately.

🛠️ Installation & Running
    -Since this program uses system("clear") and ANSI colors, it is best experienced on a Linux/Unix terminal

    -Clone the repository: 'git clone https://github.com/HaoCoder-2007/Minesweeper.git'

    -Compile the code: 'gcc minesweeper.c -o minesweeper'

    -Run the game: ./minesweeper

📝 Technical Implementation Details
    -Language: C

    -Recursion: Used for the reveal() function to handle cascading empty cells.

    -File I/O: Utilizes fopen, fprintf, and fclose to manage persistent game data.

    -Time Management: Uses the <time.h> library to track match duration with difftime.