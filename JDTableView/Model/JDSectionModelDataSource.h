//
//  JDSectionModelDataSource.h
//
//  Created by JD on 2016/9/15.
//  Copyright © 2016年 JD. All rights reserved.
//

#import <Foundation/Foundation.h>


/**
 cell type

 @param indexPath 行数信息
 @param dataInfo 行数据
 @return 行数据对应cell索引
 */
typedef NSInteger (^JDCellTypeBlock)(NSIndexPath *indexPath, id dataInfo) ;

/**
 didSelectRowAtIndexPath
 可以将block放入到cell的数据源中 支持下面3种数据的任意组合
 
 @param indexPath 行数信息
 @param dataInfo 行数据
 @param tableView view视图
 */
typedef void    (^JDDidSelectCellBlock)(UITableView *tableView,NSIndexPath *indexPath,id dataInfo) ;


@protocol JDSectionModelDataSource <NSObject>

@required
- (NSArray *)itemArray;

@optional
- (NSString *)title;

@optional

/**
  数据源对应的cell索引
 */
@property(nonatomic, copy) JDCellTypeBlock cellTypeBlock;

/**
  didSelectRowAtIndexPath
 */
@property(nonatomic, copy) JDDidSelectCellBlock didSelectCellBlock;

@end
