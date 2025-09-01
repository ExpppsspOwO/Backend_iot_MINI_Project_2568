# Dockerfile
FROM nodered/node-red:latest

# ติดตั้ง dashboard เพิ่ม (หรือ plugin อื่น ๆ ได้ที่นี่)
RUN npm install node-red-dashboard