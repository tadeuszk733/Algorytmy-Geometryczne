import sys
from vis import *
vis = Visualizer()

# dodawanie tytułu
vis.add_title('Tytuł')

# dodawanie siatki
vis.add_grid()

# punkt = (x, y)
point = (3, 7)

# odcinek = ((x1, y1), (x2, y2))
line_segment = ((-100, 500), (0, 300))

# wielokąt [(x1, y1), (x2, y2), ..., (xn, yn)]
polygon = [(1, 2), (2, 5), (4, 5), (4, 2), (2, 1)]

# koło = (x, y, radius)
circle = (0, 7, 1)

# prosta = ((x1, y1), (x2, y2))
line = ((0, 2), (1, 5))

# półprosta = ((x1, y1), (x2, y2))
half_line = ((0, 0), (3, -2))

vis.add_point(point)
vis.add_line_segment(line_segment, color='orange')
vis.add_line(line, color='red')
vis.add_polygon(polygon, alpha=0.7)
vis.add_circle(circle, color='green')
vis.add_half_line(half_line, color='purple')

# dodawanie tytułu
vis.add_title('Tytuł')

# dodawanie siatki
vis.add_grid()

# punkt = (x, y)
point = (3, 7)

# odcinek = ((x1, y1), (x2, y2))
line_segment = ((-1, 5), (0, 3))

# wielokąt [(x1, y1), (x2, y2), ..., (xn, yn)]
polygon = [(1, 2), (2, 5), (4, 5), (4, 2), (2, 1)]

# koło = (x, y, radius)
circle = (0, 7, 1)

# prosta = ((x1, y1), (x2, y2))
line = ((0, 2), (1, 5))

# półprosta = ((x1, y1), (x2, y2))
half_line = ((0, 0), (3, -2))

vis.add_point(point)
vis.add_line_segment(line_segment, color='orange')
vis.add_line(line, color='red')
vis.add_polygon(polygon, alpha=0.7)
vis.add_circle(circle, color='green')
vis.add_half_line(half_line, color='purple')
