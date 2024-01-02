# -*- coding: utf-8 -*-

from playwright.async_api import Playwright, async_playwright, expect
import asyncio
import yaml
import gc
import copy


async def run(playwright: Playwright):
    browser = await playwright.chromium.launch(headless=False, args=['--start-maximized'])
    # browser = await playwright.chromium.launch()
    context = await browser.new_context(no_viewport=True)
    page = await context.new_page()
    await page.goto("https://toolsdar.cn", timeout=200000)
    await page.wait_for_timeout(timeout=2000)
    await page.mouse.wheel(0, 1000)

    topics = await page.query_selector_all(selector=".text-gray.text-lg")
    topics = topics[1:4] + topics[5:-1]
    menus = []
    for index in range(len(topics)):
        menu_name = await topics[index].inner_text()
        menus.append(menu_name)    
    del topics

    subtopics = await page.query_selector_all(
        selector=".d-flex.flex-fill.flex-tab.align-items-center")

    nav_menus = []
    for index in range(len(menus[4:8])):
        menu_name = menus[index]
        print(f'{menu_name} {index}')
        await page.mouse.wheel(0, 1000)

        tags = []
        j = 0
        for tag in await subtopics[index].query_selector_all(selector=".nav-link.tab-noajax"):
            objects = []
            tag_name = await tag.inner_text()
            tag_id = (await tag.get_attribute('href')).split('#')[1]
            print(f'  {tag_name} {tag_id}')
            await page.get_by_role("link", name=tag_name, exact=True).click()
            await page.wait_for_timeout(timeout=5000)
            content = await page.query_selector(selector=f"#{tag_id}")
            for item in await content.query_selector_all(selector=".url-card.io-px-2.col-6"):
                name = await (await item.query_selector(
                    selector=".text-sm.overflowClip_1>strong")).inner_text()
                print(f'    {name}')
                description = await (await item.query_selector(
                    selector=".overflowClip_1.m-0.text-muted.text-xs")).inner_text()
                print(f'    {description}')
                if name not in ['Z-Library']:
                    link = await (await item.query_selector(
                        selector=".togo")).get_attribute('href')
                else:
                    link = ''
                print(f"    {link}")
                # img = await (awaititem.query_selector(
                #     selector=".lazy.unfancybox.loaded")).get_attribute('src')
                # print(f'    {img}')
                objects.append({
                    'name': name,
                    'description': description,
                    'link': link,
                    # 'img': img
                })
            tags.append({
                'name': tag_name,
                'link': f'#{tag_name}-tab',
                'active': True if j == 0 else False,
                'objects': objects
            })
            j += 1
            del content
            gc.collect()

        nav_menus.append({
            'name': menu_name,
            'tags': tags,
            'icon': 'fa fa-home',
            'active': False
        })
        

    with open('data1.yaml', 'w', encoding='utf8') as fp:
        data = {
            "title": "工具指南",
            "nav_menus": nav_menus,
            "copyright": {
                "content": "Copyright©2023-2024",
                "powerby": "工具指南",
                "link": "https://toolsdar.cn",
                "icp": "粤ICP备2022500000号-1",
                "icp_link": "https://beian.miit.gov.cn/"
            }
        }
        yaml.dump(data, fp, encoding='utf8', allow_unicode=True)

    await context.close()
    await browser.close()


async def main() -> None:
    async with async_playwright() as playwright:
        await run(playwright)


if __name__ == '__main__':
    asyncio.run(main())
