
# %%
import pandas as pd
import numpy as np

# %%
EMPTY = '.'
FILL = '#'
DIM = None

# %%


def map_nanograms(n_grams: str) -> [[int]]:
    rows = n_grams.split(' ')[:-1]

    def ch_to_num(ch): return ord(ch) - ord('A') + 1
    result = []
    for row in rows:
        row = list(map(ch_to_num, row))
        row += [0] * (DIM - len(row))
        result.append(row)
    return result


def map_board(board: str) -> [[int]]:
    rows = board.split('\\n')[:-1]

    def ch_to_num(ch): return int(ch == FILL)
    return [list(map(ch_to_num, row)) for row in rows]


def map_dataset(df: pd.DataFrame) -> ((np.ndarray, np.ndarray), np.ndarray):
    h_gram = np.array(df['h_gram'].map(map_nanograms).to_list())
    v_gram = np.array(df['v_gram'].map(map_nanograms).to_list())
    board = np.array(df['board'].map(map_board).to_list())
    return (h_gram, v_gram), board


# %%

def __read_dataset(dim: int):
    global DIM
    DIM = dim
    filename = '../dataset/{}__0.tsv'.format(DIM)
    df = pd.read_csv(filename, sep='\t', header=None,
                     names=['dim', 'board', 'h_gram', 'v_gram', ''])
    return map_dataset(df)
    # (h_gram, v_gram), board = map_dataset(df)

def flatten(data: np.ndarray) -> np.ndarray:
    return data.reshape((data.shape[0], -1))

def reshape_dataset(x, y) -> (np.ndarray, np.ndarray):
    x, y = (flatten(x[0]), flatten(x[1])), flatten(y)
    return np.hstack(x), y

def read_dataset(dim: int):
    x, y = __read_dataset(dim)
    x, y = reshape_dataset(x, y)
    return x, y