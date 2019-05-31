import os


def backup_file(src_dir, file_name, tgt_dir):
    if not os.path.isdir(tgt_dir):
        os.makedirs(tgt_dir)

    def shasum(path):
        shasum_res = os.popen(f"shasum -a 256 {path}").readlines()
        sha256, file = shasum_res[0].split()[0], shasum_res[0].split()[1]
        print(f"shasum 256 value: {sha256}, file: {file}")
        return sha256

    def copy(source, target):
        os.system(f"cp {source} {target}")
        print(f"{source} \ncopied to \n{target}")

    _src_path = os.path.expanduser(os.path.join(src_dir, file_name))
    _tgt_path = os.path.join(os.getcwd(), tgt_dir, file_name)

    if os.path.exists(_tgt_path):
        if not shasum(_src_path) == shasum(_tgt_path):
            copy(_src_path, _tgt_path)
            print("target file updated.")
        else:
            print("target file stills same.\n")
    else:
        print("target file not found.")
        copy(_src_path, _tgt_path)


def clear_spv_local_data_and_logfile(root_path, wid, clear_all=False):
    from os import remove, path, listdir
    from shutil import rmtree
    keep_log = False
    log = path.join(root_path, "spvsdk.log")
    data = path.join(root_path, wid)

    for _path in listdir(root_path):
        full_path = path.join(root_path, _path)
        if path.isdir(full_path) and _path != wid:
            keep_log = True
        if path.isdir(full_path) and _path == wid:
            rmtree(data)
            print(f"{data} removed")
        if path.isdir(full_path) and clear_all:
            rmtree(full_path)
            print(f"{data} removed")
    if path.exists(log):
        if not keep_log:
            remove(log)
            print(f"{log} removed")


class AnsiChr(object):
    class T(object):
        Default, Bold, Light, Italic, Underline, Blink, Inverse, Invisible = 0, 1, 2, 3, 4, 5, 7, 8
        # Non_Bold, Non_Underline, Non_Blink = 22, 24, 25

    class C(object):
        Black, Red, Green, Yellow, Blue, Magenta, Cyan, White, Clear_ = 0, 1, 2, 3, 4, 5, 6, 7, 8

    def __init__(self, style=T.Default, front=C.Black, back=C.White):
        self.style = style
        self.front = front
        self.back = back

    @classmethod
    def rc(cls, x):
        return cls.formatted_str(x, cls.T.Default, cls.C.Red, cls.C.Clear_)

    @classmethod
    def yb(cls, x):
        return cls.formatted_str(x, cls.T.Default, cls.C.Yellow, cls.C.Blue)

    @classmethod
    def bc(cls, x):
        return cls.formatted_str(x, cls.T.Default, cls.C.Blue, cls.C.Clear_)

    @classmethod
    def formatted_str(cls, content, style=T.Default, front=C.Red, back=C.Cyan):
        return f'\033[{str(style)};3{str(front)};4{str(back)}m{str(content)}\033[0m'

    def stain(self, content):
        return self.formatted_str(content, self.style, self.front, self.back)

    @staticmethod
    def test():
        i = 0
        for cfk, cfv in AnsiChr.C.__dict__.items():
            if cfk[0:1] != "_":
                for tk, tv in AnsiChr.T.__dict__.items():
                    if tk[0:1] != "_":
                        for cbk, cbv in AnsiChr.C.__dict__.items():
                            if cbk[0:1] != "_":
                                i += 1
                                s = "{0:3}l {2:2}{1:9} {4}{3:7} {6}{5:7}"\
                                    .format(i, tk, tv, cfk, cfv, cbk, cbv)
                                a = AnsiChr(tv, cfv, cbv).stain(s)
                                print(a, end='')
                                print(" ") if i%9 == 0 else print('', end='')


def ctprint(x, c=AnsiChr.rc, end="\n", t=True):
    colored_type = AnsiChr.bc(type(x))
    colored_value = c(x) if type(x) == str else AnsiChr.yb(x)
    s = f"{colored_type}{colored_value}" if t else f"{colored_value}"
    print(s, end=end)


