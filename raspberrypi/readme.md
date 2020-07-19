1. Pull all image repos using repo pattern name, so new ones are also discovered.
2. Scan all repos and find which files are tracked, save it as a list file.
3. Go to the Google Drive and check for new image files.
4. If new image files do exist check for download lock file.
  4.1 When lock exist stop the program.
  4.2 When no lock add it.
5. Download new files.
6. Can new files be added to a repo without reaching 10GB limit?
  6.1 Yes: add files to existing repo.
  6.2 No: create new repo and add files.
7. Push changes on repos.
8. Release lock from Google Drive and stop program.
