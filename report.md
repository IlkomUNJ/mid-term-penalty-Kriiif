Objective 1 : Analysis and Findings
As far as I can tell, in this code file we need a 3x3 matrix pattern, which requires a vertical, horizontal, and diagonal matrix.
A 3x3 pixel window was used for the analysis. This size was found to be sufficient and ideal for this task.

- Granularity: A 3x3 window is large enough to capture the fundamental characteristics of a line, such as its direction (horizontal, vertical, diagonal) and its endpoints.
- Simplicity: It is the smallest practical size that can represent connectivity between pixels without being overly complex. A larger window (e.g., 5x5) would introduce an unnecessary number of pattern variations, making the detection logic more complicated.

- Straight Lines
These patterns represent horizontal and vertical segments.
Horizontal Line:
    0 0 0
    1 1 1
    0 0 0

Vertical Line:
    0 1 0
    0 1 0
    0 1 0
    
- Diagonal Lines
These patterns represent perfect 45-degree diagonal segments.
Diagonal (Top-Left to Bottom-Right):
    1 0 0
    0 1 0
    0 0 1

Diagonal (Top-Right to Bottom-Left):
    0 0 1
    0 1 0
    1 0 0
