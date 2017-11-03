function k = crawler(url, j)

s=urlread(url);  

pat='http://[^" \n=]*.jpg';
expr = regexp(s, pat, 'match');

k = j;
for i=1:length(expr)
    a = expr(1, i);
    a = a{1, 1};
    fprintf('%s\n', a);
    try
        [s, status] = urlwrite(a, 'tmp.jpg', 'UserAgent','MATLAB R2016b','Timeout',10,'Get',{'term','urlread'});

        if status
            f=imread(s);
            [row, col, dep] = size(f);
            if row < 1920 || col < 1080 || dep < 3
                continue;
            end
            if SI(f) > 330
                fprintf('Yeah, I get another one!\n');
                imwrite(f, sprintf('images\\%d.jpg', k));
                k = k+1;
            end
        else
            fprintf('Fail to download the picture\n');
        end
    catch
        fprintf('Oh, no!!! Something is wrong!\n');
    end
end

end
