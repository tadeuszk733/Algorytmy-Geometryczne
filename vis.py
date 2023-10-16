import json
class Visualizer():
    def __init__(self) -> None:
        self.data = []

    def _write(self) -> None:
        self.f = open("commands.json", 'w')
        self.f.write(json.dumps(self.data))

    def add_title(self, title: str) -> None:
        self.data.append({'command' : 'add_title', 'title' : title})
        self._write()

    def add_grid(self) -> None:
        self.data.append({'command' : 'add_grid'})
        self._write()
    
    def add_point(self, point: tuple[float, float], color: str = 'white') -> None:
        self.data.append({'command' : 'add_point', 'x' : point[0],  'y' : point[1], 'color': color})
        self._write()

    def add_line_segment(self, line_segment: "tuple[tuple[float, float], tuple[float, float]]", color: str = 'white') -> None:
        self.data.append({'command' : 'add_line_segment', 'points': line_segment, 'color': color})
        self._write()

    def add_line(self, line: "tuple[tuple[float, float], tuple[float, float]]", color: str = 'white'):
        self.data.append({'command' : 'add_line', 'points': line, 'color': color})
        self._write()


