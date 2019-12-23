from selenium import webdriver
from selenium.webdriver.chrome.options import Options
import time
driver = webdriver.Chrome()
def main():
    url='https://cquv3.xuetangx.com/#/home'
    driver.get(url)
    start_key=int(input("输入start的视频编号: "))
    time.sleep(20)
    count=0
    with open('url_english_course.txt',"r") as f:
        for i in f:
            count=count+1
            if(count<start_key) :
                continue
            driver.get(i)
            time.sleep(10)
            try:
                video=driver.find_element_by_id('video')
                driver.execute_script("return arguments[0].play();",video)
                print('running : ',count)
            except:
                print('error : ',count)
                pass
            while(True):
                try:
                    video=driver.find_element_by_id('video')
                    print('    playing : ',count)
                    if(driver.execute_script('return arguments[0].ended;',video)==True):
                        print('    stoped')
                        break
                    driver.execute_script("return arguments[0].play();",video)
                    time.sleep(10)
                except:
                    print('    error to get information')
                    pass
main()