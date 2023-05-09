# MMT3-remote_PC_control

## Thao tác với git  
echo "Something in readme..." >> README.md  

Note: Khởi tạo git  
git init  
Note: Tạo file Readme.md  
git add README.md
git commit -m "first commit"  

Note: Chọn branch chạy  
git branch -M main  
git remote add origin https://github.com/nacon304/MMT3-remote_PC_control.git  

Note: Upload code lên  
Lần đầu: git push -u origin main  
Lần sau: git push  

Note: Kiểm tra tình trạng gửi file commit  
git status  

Note: Kiểm tra tình trạng file sau khi git push  
git log

Note: Thao tác với branch  
git branch name  
// vào branch name  
git checkout name  
// chọn branch mình xài  
git branch  
// xem branch mình xài  
git merge branch name  
// hợp code ở branch chính  
