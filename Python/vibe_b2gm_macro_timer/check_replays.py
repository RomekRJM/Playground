import mpyq
from s2protocol import versions

if __name__ == '__main__':
    archive = mpyq.MPQArchive('2022-07-12PvP.SC2Replay')

    contents = archive.header['user_data_header']['content']
    header = versions.latest().decode_replay_header(contents)
    baseBuild = header['m_version']['m_baseBuild']
    protocol = versions.build(baseBuild)

    contents = archive.read_file('replay.gamemetadata.json')

    print(contents)
