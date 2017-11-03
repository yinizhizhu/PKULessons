fileNames = fopen('urls.txt', 'r');

j = 1;
while feof(fileNames) == 0
    url = fgetl(fileNames);
    j = crawler(url, j);
end

fclose(fileNames);
